"""Integration tests: capture real X11 pixels, not an internal decoder."""
import os
from pathlib import Path
import struct
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
BIN = str(HERE / 'cell-viewer')
if '--inside-xvfb' not in sys.argv:
    sys.exit(subprocess.call(['xvfb-run', '-a', '-s', '-screen 0 1024x768x24',
                             sys.executable, __file__, '--inside-xvfb']))


def capture(expected, scale, side=8):
    deadline = time.monotonic() + 5
    while time.monotonic() < deadline:
        r = subprocess.run(['xwd', '-silent', '-name', 'cell-viewer'],
                           capture_output=True)
        if r.returncode == 0:
            h = struct.unpack('>25I', r.stdout[:100])
            offset, width, height, order, bpp, stride, colors = (
                h[0], h[4], h[5], h[7], h[11], h[12], h[19])
            data = r.stdout[offset + colors * 12:]
            if width == height == side * scale:
                actual = []
                for y in range(height):
                    for x in range(width):
                        p = y * stride + x * (bpp // 8)
                        value = int.from_bytes(data[p:p + bpp // 8],
                                               'little' if order == 0 else 'big')
                        actual.append(bool(value & (h[14] | h[15] | h[16])))
                target = [expected[(y // scale) * side + x // scale]
                          for y in range(height) for x in range(width)]
                if actual == target:
                    return
        time.sleep(0.02)
    raise AssertionError('rendered pixels did not match the expected pattern')


def packed(bits):
    return bytes(sum(bits[i + j] << j for j in range(8))
                 for i in range(0, len(bits), 8))


for scale in (1, 3):
    p = subprocess.Popen([BIN, '-s', '3', '-z', str(scale)],
                         stdin=subprocess.PIPE, stderr=subprocess.PIPE)
    try:
        for bits in ([0] * 64, [1] * 64,
                     [int(i in (0, 7, 8, 22, 63)) for i in range(64)],
                     [int((i // 8 + i % 8) % 2 == 0) for i in range(64)]):
            data = packed(bits)
            # Deliberately split a frame across multiple writes.
            p.stdin.write(data[:3]); p.stdin.flush()
            time.sleep(0.03)
            p.stdin.write(data[3:]); p.stdin.flush()
            capture(bits, scale)
        p.stdin.close()
        time.sleep(0.1)
        assert p.poll() is None, 'last frame should remain at EOF'
        capture(bits, scale)
    finally:
        p.terminate(); p.wait(timeout=5)

for data, status, message in [(b'', 0, b'0 frames'),
                              (bytes(16), 0, b'2 frames'),
                              (bytes(9), 1, b'truncated frame')]:
    r = subprocess.run([BIN, '-S', '8', '--exit-on-eof'], input=data,
                       capture_output=True, timeout=5)
    assert r.returncode == status and message in r.stderr, r
for args in (['-s', '0'], ['-S', '9'], ['-z', '0'], ['-z', '8192'],
             ['-s', '14'], ['-S', '8junk'], ['unexpected']):
    assert subprocess.run([BIN] + args, capture_output=True).returncode == 2
assert subprocess.run([BIN, '--help'], capture_output=True).returncode == 0
r = subprocess.run([BIN], stdin=subprocess.DEVNULL, capture_output=True,
                   env={**os.environ, 'DISPLAY': ''})
assert r.returncode == 1 and b'cannot open' in r.stderr
# A directory descriptor provokes an actual read error.
fd = os.open(HERE, os.O_RDONLY)
try:
    r = subprocess.run([BIN], stdin=fd, capture_output=True, timeout=5)
    assert r.returncode == 1 and b'stdin' in r.stderr
finally:
    os.close(fd)
# Audit the actual engine, then stream all 1024 frames through the viewer.
root = HERE.parent.parent
command = [str(root / 'old/cell/src/cell'), '-s', '9', '-l', '1024',
           '-k', '0', '-e', '8', '-t', str(root / 'old/cell/rule/life.t'),
           '-f', str(root / 'old/cell/frame/random-9-0')]
r = subprocess.run(command, capture_output=True, timeout=60)
assert r.returncode == 0 and not r.stderr and len(r.stdout) == 1024 * 32768
initial = (root / 'old/cell/frame/random-9-0').read_bytes()
assert r.stdout[:32768] == packed([v & 1 for v in initial])
nxt = []
for y in range(512):
    for x in range(512):
        count = sum(initial[((y + dy) % 512) * 512 + (x + dx) % 512] & 1
                    for dy in (-1, 0, 1) for dx in (-1, 0, 1) if dx or dy)
        nxt.append(int(count == 3 or (count == 2 and initial[y * 512 + x] & 1)))
assert r.stdout[32768:65536] == packed(nxt)
last = [((b >> j) & 1) for b in r.stdout[-32768:] for j in range(8)]
engine = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
viewer = subprocess.Popen([BIN, '-s', '9'], stdin=engine.stdout,
                          stderr=subprocess.PIPE)
engine.stdout.close()
try:
    assert engine.wait(timeout=60) == 0
    import select
    assert select.select([viewer.stderr], [], [], 60)[0], 'viewer did not reach EOF'
    assert b'EOF after 1024 frames' in viewer.stderr.readline()
    capture(last, 1, 512)
finally:
    viewer.terminate(); viewer.wait(timeout=5)
    if engine.poll() is None:
        engine.terminate(); engine.wait(timeout=5)
print('PASS: raw Life audit, independent Conway step, full pipeline, final X11 pixels')
print('PASS: X11 pixels, LSB order, frame boundaries, scales 1/3, EOF, errors, options')
