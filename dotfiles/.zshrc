export PATH="$PATH:$HOME/cp"
export PATH="/Library/TeX/texbin:$PATH"
export PATH="$PATH:$HOME/bin"
export PATH="$PATH:$HOME/code/competitive-programming/scripts"
export PATH="$PATH:$HOME/Code/Competitive-Programming/scripts"

eval "$(zoxide init zsh)"

[ -f ~/.fzf.zsh ] && source ~/.fzf.zsh

new() {
    cd /Users/mtbishmam/code/competitive-programming/practice || return 1
    cp -n template.cpp "$1"
    vim "$1"
}
