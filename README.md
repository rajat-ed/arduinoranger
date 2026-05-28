# Motion Lab

A browser-based data logger for Arduino ultrasonic sensors. Connect an HC-SR04, record displacement, velocity, and acceleration in real time, and export your data — all from a single HTML file with no install required.

![Motion Lab Screenshot](docs/screenshot.png)

---

## Features

- **Live plotting** — real-time graphs for displacement, velocity, and acceleration
- **Fullscreen mode** — expand any graph to full screen while recording; press Esc to exit
- **Demo mode** — simulated oscillation data, no hardware needed
- **CSV export** — one-click download of all recorded samples
- **Graph snapshots** — save any chart as a PNG
- **Unit toggle** — switch between cm / cm/s and m / m/s on the fly
- **Smoothing** — configurable moving-average filter to reduce sensor noise
- **Zero dependencies** — single `.html` file, works offline after first load

---

## Hardware

| Component | Pin |
|-----------|-----|
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| HC-SR04 TRIG | D5 |
| HC-SR04 ECHO | D6 |

Any Arduino-compatible board with USB serial works (Uno, Nano, Mega, etc.).

---

## Quick Start

### 1. Flash the Arduino

Upload `arduino/motion_lab.ino` to your board using the Arduino IDE or CLI.

```
arduino-cli compile --fqbn arduino:avr:uno arduino/motion_lab
arduino-cli upload  --fqbn arduino:avr:uno -p /dev/ttyUSB0 arduino/motion_lab
```

Default baud rate is **9600**. Change `INTERVAL_MS` in the sketch to adjust sample rate.

### 2. Open the app

Open `index.html` directly in **Chrome** or **Edge** (Web Serial API required — Firefox is not supported).

```
# macOS / Linux
open index.html

# or just double-click it in your file manager
```

### 3. Connect and record

1. Click **Connect Arduino** and select your serial port
2. Click **Record** to start capturing data
3. Move an object in front of the sensor
4. Click **Export to CSV** when done

---

## Browser Compatibility

| Browser | Supported |
|---------|-----------|
| Chrome 89+ | ✅ |
| Edge 89+ | ✅ |
| Firefox | ❌ (no Web Serial API) |
| Safari | ❌ (no Web Serial API) |

---

## Repository Structure

```
motion-lab/
├── index.html              # Main application (self-contained)
├── arduino/
│   └── motion_lab.ino      # Arduino sketch for HC-SR04
├── docs/
│   ├── screenshot.png      # App screenshot for README
│   ├── wiring-diagram.png  # Hardware wiring reference
│   └── physics-notes.md    # Derivation of velocity/acceleration from sensor data
├── examples/
│   ├── bouncing-ball.csv   # Sample dataset — ball drop
│   ├── spring-mass.csv     # Sample dataset — spring oscillation
│   └── cart-ramp.csv       # Sample dataset — cart on inclined ramp
├── CONTRIBUTING.md
├── LICENSE
└── README.md
```

---

## Configuration

All settings are accessible in the UI. For defaults, edit the top of the `<script>` block in `index.html`:

| Setting | Default | Description |
|---------|---------|-------------|
| Baud Rate | 9600 | Must match `Serial.begin()` in the sketch |
| Sample Rate | 5 Hz (200 ms) | How often Arduino sends a reading |
| Max Points | 200 | Rolling buffer size for graphs |
| Smoothing | 3 | Moving-average window (1 = off) |

---

## Physics

Velocity and acceleration are derived numerically from the raw distance readings:

```
v(t) = Δs / Δt        (finite difference, first derivative)
a(t) = Δv / Δt        (finite difference, second derivative)
```

Smoothing is applied to displacement before differentiation to reduce noise amplification. For cleaner acceleration data, increase the smoothing window or decrease the sample rate.

---

## License

MIT — see [LICENSE](LICENSE).
