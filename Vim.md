# Vim Editor

Ctrl-C |> Normal Mode (Ctrl-C/Ctrl-V/Ctrl-f will not work for copy/paste)

i/a/I/A/o/O |> Insert Mode

| Command | Description |
|---------|-------------|
| ESC or Ctrl-c | Go back to **Normal Mode** |
| i | Go to **Insert Mode** |
|  h | |
| j | |
| k | |
| l | |
| w | jump from word to work (forward) |
| b | jump from word to work (backward) |
| e | jump to the end of the word |
| ge | jump to the end of word (backword) |
| W, B, E, GE | Include special character with w, b, e, ge |
| f{char} | find the next occurance of {char} |
| t{char} | (until) move curser just before the occurance of {char}, After using f{char}, use `;` to go to next occurance, `,` to go to previous |
| 0 | Move to first character in a line |
| ^ | Move to first non-blank character of a line |
| $ | Move to end of line |
| g_ | Move to non-blank character at the end of line |
| } | jump entire paragrahp downward |
| { | jump entire paragraph upward |
| Ctrl-D | move down half page |
| Ctrl-U | move up half page |
| /{pattern} | search forward, `n` to jump to next match, `N` to jump to previous |
| ?{backward} | search backward |
| /<Enter> | run last search forward |
| ?<Enter> | run last search backward |
| * | search for the word under cursor |
| {count}motion | multiply a motion count times |
| 2w | move cursor 2 word forward |
| gd | jump to definition of whatever is under the cursor |
| gf | jump to a file in import |
| gg | jump to the top of the file |
| {line}gg | jump to a specific line |
| G | go to end of file |
| % | jump to matching ({[]}) |
| {operator}{count}{motion} | |
| d5j or d5 | delete 5 lines down |
| df' | deletes everything in the current line until the first occurrence of the ' including ' |
| dt' | deletes everything in the current line until the first occurrence of the ' excluding ' |
| d/hello | delete everything until the first occurance of hello |
| dd | delete whole line |
| cc | change a whole line |
| D | delete from cursor till end of line |
| C | change from cursor till end of line |
| . |
| i | insert mode before cursor |
| a | append, insert mode after cursor |
| I | insert mode at the beginning of current line |
| A | insert mode at the end of current line |
| o | Insert new line below |
| O | Insert new line above |
| gi | puts u into insert mode at the last place you left insert mode |
| Ctrl-h | delete last character you typed |
| Ctrl-w | delete last word you typed |
| Ctrl-u | delete last line you type |
| v | visual mode character-wise |
| V | visual mode line-wise |
| Ctrl-V | visual mode block-wise |
| :sp {name-of-file} | horizontal split |
| :vsp {name-of-file} | vertical split |
| <Ctrl-W> + hjkl | move between split windows |
| :tabnew {file} | open a file in new tab |
| :tabn | go to next tab |
| :tabp | go to previous tab |
| yiw | yank in current word |
| yaw | yank all word (includes a trailing space) |
| yy | yank the current line |
| 3yy | yank three lines starting at the current one |
| yap | yank all paragraph (includes trailing newline) |
| ~    | Changes the case of current character |
| guu  | Change current line from upper to lower |
| gUU  | Change current LINE from lower to upper |
| guw  | Change to end of current WORD from upper to lower |
| guaw | Change all of current WORD to lower |
| gUw  | Change to end of current WORD from lower to upper |
| gUaw | Change all of current WORD to upper |
| g~~  | Invert case to entire line |
| g~w  | Invert case to current WORD |
| guG  | Change to lowercase until the end of document |
| gU)  | Change until end of sentence to upper case |
| gu}  | Change to end of paragraph to lower case |
| gU5j | Change 5 lines below to upper case |
| gu3k | Change 3 lines above to lower case |
| yw   | Yank word              |
| yaw  | Yank entire word irrespecitive of where the cursor is located    |
| yiw  | Yank entire word            |
| :tabnew | open new tab |
| gt   | Move to next tab            |
| gT   | Move to previous tab              |
| _nnn_ gt     | Move to numbered tab              |

In visual mode you select the text first and then you type operator

vim commands
d - delete
c - change
y - yank
p - paste
g~ - toggle caps
. - repeat the last change you made

| CMD   | Description |
|-------|-------------|
| `d2w` | Delete two words |
| `cis` | Change inside sentence (delete curr one and enter insert mode) |
| `yip` | Yank inside parapgraph (copy curr paragraph) |
| `ct<` | Change to open bracket (change till open bracket) |
| `*`   | search for other instance of the word under cursor |
| `C`   | change current line from where you're at |
| `S`   | substitute the entire current line |
| `dt.` | delete from where you are to the period |
| `D`   | delete to the end of line |
| `J`   | Join current line with next one |
| `dw` - `5.` | delete a word - delete five more words |
| `ddp` | switching lines of text |
| `v`   | character-based visual mode |
| `V`   | line-based visual mode |
| `Ctrl-v` | paragraph-based visual mode |


# ProVim

| CMD | Description |
|-----|--------------|
| `:sp` | Split current buffer |
| `:history` | static list |
| `q:` | dynamic list |
| `:read f2.txt` | read content of f2.txt into current file |
| `:8read f2.txt` | insert in f2.txt at line 8 |

### Moving between files

| CMD | Description |
| `:bn` | Move to next buffer |
| `:b5` | Move to 5th buffer |
| `:bp` | Move to previous buffer |
| `:ls` | list all buffers |
| `:b#` | move to alternative buffer |
| `:bf` | Move to first buffer |
| `:bl` | Move to last buffer |
| `:bm` | Move to next modified buffer |
| `:5,9wq` | Save changes from line 5-9 only |



**Double an operator to make it operate on a whole line**: dd deletes a whole like, cc changes a whole line, etc.
Capitalize an operator to make it operate from the cursor to the end of a line: D deletes from the cursor to the end of the line, C changes to the end of a line, etc.

this is a WORD: Iam_A_WORD(WORD)
this function call sum(2,3) is also a WORD
this array [1,2,3,4,5] is a WORD as well


const fireball = function(target){

:set nowrapscan; this prevents Vim from wrapping to top when it hits the bottom.

%s/old/new/gc => interactive replace, [c] confirm each substitution
