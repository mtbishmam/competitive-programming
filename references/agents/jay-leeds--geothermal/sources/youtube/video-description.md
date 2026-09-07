# My Competitive Programming Setup — video description

Source: https://www.youtube.com/watch?v=S48QUOIkoNc

In this video, I discuss my competitive programming setup, including my
terminal, editor, and stress testing scripts.

## Links

- WSL Setup Guide: https://docs.microsoft.com/en-us/windows/wsl/install-win10
- WSLtty Setup Guide (with Solarized Light Theme):
  https://www.steventammen.com/old-posts/basic-wsl-setup/
- Path to WSL Files: `\\wsl$\Ubuntu`
- `.vimrc`: https://pastebin.com/khJS1zmN — make sure to enter the path to
  your template.
- My Template: https://pastebin.com/qkM21FGb
- Vundle: https://github.com/VundleVim/Vundle.vim — not mentioned in the
  video, but required to use the listed Vim plugins.

Other recommended editors if Vim is not your preference:

- CLion: https://www.jetbrains.com/clion/
- VS Code: https://code.visualstudio.com/
- Geany: https://geany.org/
- Sublime Text: https://www.sublimetext.com/

## Lines for `.bashrc`

```sh
ulimit -s unlimited
export PATH=$PATH:~/scripts/
```

The parenthetical explanations and list dashes are not part of the shell
commands.

## Scripts placed in `~/scripts`

- `build.sh`: https://pastebin.com/xhw4rLfn
  - Format: `build.sh A`
  - Compiles `A.cpp` into executable `A`.
- `stress.sh`: https://pastebin.com/MkfwM3S9
  - Format: `stress.sh solutionA solutionB generator numTests`
  - Runs both solutions against generator outputs and reports the first
    disagreement.
- `validate.sh`: https://pastebin.com/zuRze3aW
  - Format: `validate.sh solution validator generator numTests`
  - Runs the solution, feeds input plus output to the validator, and reports
    the first result not beginning with `OK`.
- `interact.sh`: https://pastebin.com/eEFx47Nv
  - Format: `interact.sh solution interactor numTests`
  - Runs the solution against the interactor and reports the first interaction
    whose final interactor output is not `OK`.
  - The local path to `runner.py` must be configured in this script.
- `runner.py`: https://pastebin.com/q5GjQCT3
  - Required by `interact.sh`.
