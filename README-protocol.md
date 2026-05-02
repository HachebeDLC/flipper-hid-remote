# Flipper HID Remote Protocol

This document describes the Bluetooth protocol used between the web remote in
`src/web` and the Flipper application.

## Transport

The web client talks to the Flipper over the Momentum/Xtreme BLE serial service.
It discovers devices whose advertised name starts with `HID_`, connects to the
serial service, and writes command packets to the RX characteristic.

| Item | Value |
| --- | --- |
| Advertised name | `HID_` followed by the Flipper device name |
| Serial service UUID | `8fe5b3d5-2e7f-4a98-2a48-7acc60fe0000` |
| RX characteristic UUID | `19ed82ae-ed21-4c9d-4145-228e62fe0000` |
| Optional services requested by web client | Serial service, `battery_service` |
| Write method | `writeValueWithoutResponse`, falling back to `writeValue` |

The Flipper app starts the serial BLE profile with bonding enabled and the
pairing method set to PIN-code display. It also applies a stable app-specific
BLE identity by changing the advertisement name to `HID_[device name]` and
XORing the base MAC address in a fixed way. This lets the browser find only this
remote app and helps existing bonds survive app restarts.

## Packet Format

All application commands are short binary packets:

```text
[type][payload...]
```

`type` is one byte. The payload length depends on the command. Multi-byte
framing, checksums, sequence numbers, responses, acknowledgements, and retries
are not part of the application protocol.

The current Flipper receive path copies at most 3 bytes from each BLE serial
receive event into an internal queue. Existing commands are therefore 2 or
3 bytes long. Unknown packet types and packets shorter than the required length
are rejected by `FlipperProtocolParse`.

## Commands

| Type | Name | Packet | Payload interpretation | Action |
| --- | --- | --- | --- | --- |
| `0x01` | Keyboard character | `[0x01, ascii]` | `ascii` is a single 7-bit character code. | Looks up the character in the active keyboard layout, presses it for about 60 ms, then releases it. |
| `0x02` | Mouse move | `[0x02, dx, dy]` | `dx` and `dy` are signed 8-bit relative movement deltas. | Moves the USB HID mouse by the relative delta. Optional Flipper-side acceleration may modify the delta before injection. |
| `0x03` | Key down | `[0x03, hid_code]` | `hid_code` is an 8-bit USB HID keyboard usage ID. | Presses the HID key and leaves it held. |
| `0x04` | Key up | `[0x04, hid_code]` | `hid_code` is an 8-bit USB HID keyboard usage ID. | Releases the HID key. |
| `0x05` | Set modifiers | `[0x05, mask]` | `mask` is the modifier bitmask described below. | Replaces the current modifier state used for later keyboard commands. |
| `0x06` | Mouse buttons | `[0x06, mask]` | `mask` is the mouse button bitmask described below. | Presses the requested mouse buttons, or releases all buttons when `mask` is `0x00`. |
| `0x07` | Mouse scroll | `[0x07, delta]` | `delta` is a signed 8-bit wheel delta. | Sends a relative USB HID mouse wheel event. |

## Modifier Mask

The browser sends the same 8-bit modifier layout used by BadUSB keyboard layout
files:

| Bit | Value | Meaning |
| --- | --- | --- |
| 0 | `0x01` | Left Control |
| 1 | `0x02` | Left Shift |
| 2 | `0x04` | Left Alt |
| 3 | `0x08` | Left GUI / Command |
| 4 | `0x10` | Right Control |
| 5 | `0x20` | Right Shift |
| 6 | `0x40` | Right Alt |
| 7 | `0x80` | Right GUI / Command |

`Set modifiers` stores the mask globally on the Flipper side. Later `Keyboard
character`, `Key down`, and `Key up` commands are ORed with that stored modifier
state when injected over USB HID. Sending `[0x05, 0x00]` clears all modifiers.

The current web UI exposes the first four bits. In iOS mode, the browser maps
the physical Control key to GUI/Command (`0x08`) instead of Left Control
(`0x01`).

## Mouse Button Mask

| Bit | Value | Meaning |
| --- | --- | --- |
| 0 | `0x01` | Left button |
| 1 | `0x02` | Right button |
| 2 | `0x04` | Middle button, supported by the HID report but not exposed by the current web UI |

Any non-zero mask calls the Flipper mouse press function with that mask and keeps
the button state held, which enables dragging. A zero mask releases all mouse
buttons.

## Signed Byte Values

Mouse movement and scroll payload bytes are interpreted by the firmware as
`int8_t`. A client should encode negative values using two's complement:

| Decimal | Encoded byte |
| --- | --- |
| `1` | `0x01` |
| `-1` | `0xFF` |
| `127` | `0x7F` |
| `-128` | `0x80` |

The current web client creates these values with `value & 0xFF`.

## Web Client Behavior

The web UI serializes writes through a small JavaScript queue and waits 12 ms
between queued actions. Mouse movement is accumulated and flushed every 25 ms as
a single `Mouse move` packet. Tap-to-click sends left-button down, waits 30 ms,
then sends button release. Special keys such as Backspace and arrows are sent as
`Key down`, a 30 ms delay, then `Key up`.

Printable text entered through the hidden text input is sent one character at a
time with `Keyboard character`, so it depends on the active layout selected in
the Flipper app. Special-key commands use USB HID usage IDs directly and do not
go through the ASCII layout lookup.

## Examples

Type lowercase `a`:

```text
01 61
```

Press Enter through the ASCII path:

```text
01 0A
```

Move the mouse right by 12 and up by 3:

```text
02 0C FD
```

Hold Shift, tap the HID `A` usage (`0x04`), then clear modifiers:

```text
05 02
03 04
04 04
05 00
```

Left-click:

```text
06 01
06 00
```

Scroll down one step as sent by the current web client:

```text
07 FF
```
