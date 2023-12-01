<h1 id="-pipex">↪️ Pipex</h1>
<p>This project in C was coded as part of my studies at school 42.<br>
Pipex consists of reproducing a pipe in shell with redirection of standard input and redirection of standard output.<br>
For more information on the project and its constraints, I recommend that you read the topic provided in the repo !<br><br>
When executing, please respect "./pipex file1 cmd1 cmd2 file2", which corresponds in shell to "< file1 cmd1 | cmd2 > file2".</p>

<h2 id ="-bonus part">⭐ Bonus Part</h2>
<p>For this project, there are two different bonuses.<br>
- Managing several pipes: "./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2" will reproduce the operation of "< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2" in shell.<br>
- heredoc and redirection of standard output in APPEND mode when the first parameter is "here_doc": "./pipex here_doc LIMITER cmd cmd1 file" reproduces the operation of "cmd << LIMITER | cmd1 >> file" in shell.<br><br>
To access the bonuses, type “make bonus”.</p>
