export PATH="$HOME/cp:$HOME/code/competitive-programming/scripts:$PATH"
export CC=gcc-16 CXX=g++-16
alias gcc=gcc-16 g++=g++-16 c++=g++-16

eval "$(zoxide init zsh)"
[ -f ~/.fzf.zsh ] && source ~/.fzf.zsh

new() {
    cd /Users/mtbishmam/code/competitive-programming/practice || return 1
    cp -n template.cpp "$1.cpp"
    vim "$1.cpp"
}
