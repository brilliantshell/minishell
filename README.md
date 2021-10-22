# minishell
42 Minishell project by yongjule &amp; ghan


| Date | Log|
|:---:|:---:| 
|2021-09-08|Start minishell|
|2021-10-12|There was leaks|
|2021-10-16|Bash is Wrong|
|2021-10-20|![score](https://badge42.herokuapp.com/api/project/yongjule/minishell)|


---
## To-do List

- [x] 팀 이름 정하기
- [x] [git organization](https://github.com/brilliantshell/minishell) 만들기

- [x] 함수 공부

- [x] 깃 컨벤션 - 커밋 메시지 통일

  [PREFIX] [SUFFIX] : [description]

  - prefix
    - m_ : mandatory
    - b_ : bonus
  - suffix
    - feat : 기능에 대한 설명
    - fix : 수정한 부분 
    - norm : 놂
    - etc

- [x] 디렉토리 시스템

  - /root
    - /includes
    - /src
      - parse
      - exec
	  - redir
      - builtin

- [x] 섹션 구분, 분업

  - [ghan](https://github.com/42ghan)
    - signal handling
    - build terminal structure
	- builtin command
	- data preprocessing
  - [yongjule](github.com/yongjulejule)
	- pipe system
	- redirections
    - execute command

---

## Reference

- _[GNU Readline Library description](https://web.mit.edu/gnu/doc/html/rlman_2.html)_
- _W. Richard Stevens & Stephen A. Rago (2013). Advanced Programming in the UNIX Environment (3rd ed.) U.S. : Addison-Wesley_
- _[Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/index.html)_
- _[GNU Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)_
- _[bash source code](https://tiswww.case.edu/php/chet/bash/bashtop.html#Availability)_
- _[GNU C Library](https://www.gnu.org/software/libc/manual/html_node/index.html)_
