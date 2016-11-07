# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
# $- 는 현재 system flag를 뜻하며 기본값은 himBH 이다.
# flag에 i(interactive)가 없다면 아무 행동도 하지 않음
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
# 중복 수행된 라인(명령)이나 공백으로 시작하는 라인은 history에 넣지 않음.
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
# 쉘 옵션 설정, history를 history파일(.bash_history)에 추가하도록 함
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
# HISTSIZE : 세션이 활성화 상태일 때 메모리상에 저장되는 history line size.
# HISTFILESIZE : history file(.bsah_history)에 저장되는 line size.
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
# 쉘이 각 명령 다음에 윈도우 사이즈를 체크하고 필요하다면 LINES 와 COLUMNS 변수의 값을 업데이트.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
# 해당 옵션을 사용되면 pathname 확장 컨텍스트에서 "**" 패턴으로 해당 경로상의 모든
# 파일과 하위 디렉터리들을 매칭시킬 수 있음
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
# 텍스트 형식이 아닌 파일에 대해 less 명령어가 좀 더 잘 작동하도록 해주는 라인
# less 명령은 input file에 대해 내용을 쉘에 뿌려주는 기능을 함
# 파일의 아래로만 스크롤 가능한 more와 달리 less는 위아래로 탐색 가능
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
# chroot를 지정하는 변수 설정. 만약 debian_chroot 변수 값이 비어있다면
# /etc/debian_chroot 파일의 값을 읽어 설정함
# chroot는 루트 디렉토리를 말함
# 예) chroot가 /home/maanager 이면 cd / 시 실제로는 /home/manager가 됨
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
# 프롬프트에서 색상을 표현할 수 있도록 설정
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
# 컬러 프롬프트 강제 활성화 (터미널이 지원하는 경우)
# 기본으로 프롬프트 보단 명령어 출력에 중점을 두기 위헤 비활성
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

# bash prompt 출력 형식 설정 부분 (기본값이 chroot 아래 username@hostname:/absolute_path$)
# 만약 컬러 프롬프트 옵션이 yes 라면 색상을 포함해서 출력
# 아니면 색상 없이 위 형식으로 프롬프트를 출력한다.
# Lab-1 Task-2 를 수행하기 위해서는 w 옵션을 W로 바꾸면 현재 폴더를 상대경로로 보여줌
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
# xterm이라면 프롬프트 형식을 user@host:dir 로 설정
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
# ls 명렁어에서 폴더 색상표시 기능 활성화 및 명령어 alis 선언
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# colored GCC warnings and errors
# GCC 에러 컬러 출력 활성화
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
# ls 명령어 추가 alias
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
# 오래 수행되는 명령어를 위한 alert 명렁어 alias
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.
# Alias 를 .bashrc에 바로 넣기 보단 .bash_aliases같은 다른 파일에 선언하는 것이 바람직하다.
# 사용자 홈폴더에 .bash_aliases 파일이 있다면 해당 내용을 수행함.
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
# 명령어 자동 완성 기능(탭키 눌렀을 때 작동) 활성화 구문
# 쉘이 posix 모드이면 작동하지 않음.
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi
