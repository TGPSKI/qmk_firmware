# Current status

- partially implemented desktop rx for indicators 
- see raw hid for more notes

# RAW HID Modifications + Tab Save

- removed via enable from rules.mk
- wireless features turned off to enable console
- some dangling code hanging around
- made mods to keychron common to debug raw hid rx

## Modified files

```
modified:   keyboards/keychron/common/keychron_common.c
modified:   keyboards/keychron/common/keychron_common.h
modified:   keyboards/keychron/q0_max/encoder/keymaps/TGPSKI/TGPSKI.h
modified:   keyboards/keychron/q0_max/encoder/keymaps/TGPSKI/keymap.c
modified:   keyboards/keychron/q0_max/encoder/keymaps/TGPSKI/rules.mk
modified:   keyboards/keychron/q0_max/info.json
```

## Tabs

* https://docs.qmk.fm/features/rawhid
* https://getreuer.info/posts/keyboards/triggers/index.html
* https://docs.qmk.fm/ref_functions#software-timers
* https://skullydazed.github.io/portfolio/

# Notes in spreadsheet format
https://docs.google.com/spreadsheets/d/15q6G1t_yyHRp5JXujypRtJ08vjSGq8-7QQqVM2zY4cg/edit?gid=0#gid=0

# Active

- clean up code
- create function for the repetitive bits in masking

- desktop indicator leds (kwin script and usb hid feature reports)
-- spent a lot of time on this
-- im super close though!
-- https://docs.qmk.fm/features/rawhid
-- https://github.com/qmk/qmk_firmware/issues/9028
-- 

- unlock / lock
- concepts for page 1 and page 2
- select word (https://getreuer.info/posts/keyboards/select-word/index.html)
- select line (see above)
- visual studio page
- google stuff
- launchers? morning routines?

# Complete

- Select layers
- Layer indicators + custom color option
- Software enter DFU
- Dekstop Switch
- Active window to desktop
- Ultrawide windows
    - 3x2 2U
    - 3x1 1U + 2U
    - 2x2 1U
    - 2x1 and 1x2 1U
    - maximize
    - minimize
- show all
- zoom in / out / reset
    - active window
    - desktop
- add glowing eyes to skull

# Unfinished / Abandoned

- ctrl - shift - f4 (select next window, with mod delay)
https://docs.qmk.fm/features/repeat_key#handle-how-a-key-is-repeated







