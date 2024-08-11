ls '-la'       ;
ls | wc << a ; pipe erros stdin; done!
export var="ls .";
$var]  == ls .]

export var="s ." 

l$var. 

echo  $"PATH" ==> PATH not $PATH

<< $USER   ==== do not expand the delimeter

minishell> ls > # | ls 
Syntax error: unexpected token '#'
minishell> ls > # | ls  | pwd
Syntax error: unexpected token '#'
minishell> echo $?
0
minishell> bash
yozainan@c3r10p1:~/Desktop/V_5$ ls > # | ls
bash: syntax error near unexpected token `newline'
yozainan@c3r10p1:~/Desktop/V_5$ echo $?
2
yozainan@c3r10p1:~/Desktop/V_5$ 

need fix exit_status;

minishell> pwd
/nfs/homes/yozainan
minishell> cd Desktop/
minishell> export | grep OLDPWD
declare -x OLDPWD
minishell> export | grep PWD
declare -x OLDPWD
minishell> export PWD
minishell> ls
DALLE_2023-10-29_19.12.22_-_ground_and_stripe_in_the_middle.png  philosopher  V_5
minishell> cd ..
minishell> export | grep PWD
declare -x OLDPWD
declare -x PWD="/nfs/homes/yozainan"
minishell> cd ..
minishell> cd 
minishell> cd 
minishell> export | grep PWD
declare -x OLDPWD="/nfs/homes/yozainan"
declare -x PWD="/nfs/homes/yozainan"
minishell>


need fix OLPWD not depand in pwd ---> [done] 
/*********************  funciton have leaks **********************/
/************* builtins  have double free ************/
[x] cd;
[x] export;
[ok] unset;
[ok] pwd;
[ok] env;
[ok]exit;
[ok] echo;

while true; do valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./your_program; sleep 1; done

