# VIM Hacks

## Saving a File

| Save Methods | Description |
|--------------|-------------|
| `:w` (or) `:write` | Save working file |
| `:up` (or) `:update` | Save working file |
| `:w newfile.txt` | Save as newfile.txt |
| `:up newfile.txt` | Save as newfile.txt |
| `:w! newfile.txt` | Save as newfile.txt (with overwrite option)|
| `:up! newfile.txt` | Save as newfile.txt (with overwrite option) |

## Closing a File

| Quit Methods | Description |
|--------------|-------------|
| `:x`  | Save working file and exit |
| `:wq` | Save working file and exit |
| `ZZ`  | Save working file and exit |
| `:q!` | Exit without saving working file |
| `:qa` | Exit all open files in the current Vim session |

## Types of Vim Modes

| Mode | Description |
|------|-------------|
| `Normal` | The Vim editor starts in this mode, where you can execute all editor commands. |
| `Insert` | This mode is for inserting text. |
| `Command Line` | This mode is for executing ex commands at the bottom of the editor. For example, :wq |

## Advanced Modes

| Mode | Description |
|------|-------------|
| `Visual` | You can select text (Using v, V or CTRL-V) in visual mode and execute Vim commands. For example, you can select a column of text and delete in visual mode. |
| `Select` | From :help vim-modes-intro “Typing a printable character deletes the selection and starts Insert mode. In this mode, "-- SELECT --" is shown at the bottom of the window.” |
| `Ex` | From :help vim-modes-intro “Like Command-line mode, but after entering a command you remain in Ex mode” |

## Moving around a File

| Navigation Key | Description |
|----------------|-------------|
| `j` | Down one line |
| `k` | Up one line |
| `h` | Move right one character |
| `l` | (lower-case L) Move left one character |

## Vim Configuration File (~/.vimrc)

| OS | Location |
|----|-----------|
| `UNIX/Linux` | `$HOME/.vimrc` Example: /home/ramesh/.vimrc |
| `Windows` | `$HOME/_vimrc` Example: C:\Documents and Settings\ramesh\_vimrc Note: On Windows there is a _ (underscore) before vimrc |

## Global Vimrc

| OS | Location |
|----|----------|
| `UNIX/Linux` | $VIM/.vimrc Example: /usr/share/vim/.vimrc |
| `Windows` | $VIM/_vimrc Example: C:\Program Files\Vim\_vimrc |

## All About Vim Help

| Help | Description |
|-------|------------|
| `:help (or) :h` | Vim built in help documentation |
| `:helpgrep pattern` | Search help using pattern. For example, :helpgrep saveas Tip: Use :cn to jump for next occurrence of the pattern. |
| `:help 'option'` | Help on a Vim set option. For example: :help ‘list’ will give help about :set list |
| `:help CTRL-X` | Help on Vim CTRL-X command. Use the same concept to get help on other CTRL- Vim commands. |
| `:help :x` | Help on Vim :x command Use the same concept to get help on other : Vim  commands. |
| `:help\<CTRL-D\>` | Help on auto completion. For example: help\<CTRL-D\> will show all commands that starts with help. |

## Scroll Full Page or Half Page

| Navigation Key | Description |
|----------------|-------------|
| `CTRL-F` | Scroll down full page |
| `CTRL-B` | Scroll up full page |
| `CTRL-D` | Scroll down half page |
| `CTRL-U` | Scroll up half page |
| `CTRL-E` | Scroll down one line |
| `CTRL-Y` | Scroll up one line |

## Word Navigation

| Navigation Key | Description |
|----------------|-------------|
| `w` | Go to the beginning of next word |
| `W` | Go to the beginning of next WORD |
| `e` | Go to the end of current word |
| `E` | Go to the end of current WORD |
| `b` | Go to the beginning of previous word |
| `B` | Go to the beginning of previous WORD |

## Position cursor at specific location within a line

| Navigation Key | Description |
|----------------|-------------|
| `0 (zero)` | Go to the starting of current line |
| `$ (dollar sign)` | Go to the end of current line |
| `^ (caret sign)` | Go to the first non blank character of current line |
| `g_` | Go to the last non blank character of current line |

## Paragraph, Section, Sentence Navigations

| Navigation Key | Description |
|----------------|-------------|
| `{`  | Go to the beginning of current paragraph |
| `}`  | Go to the beginning of next paragraph |
| `[[` | Go to the beginning of the current section |
| `]]` | Go to the beginning of next section |
| `(`  | Go to the beginning of previous sentence |
| `)`  | Go to the beginning of next sentence |

## Screen Navigation

| Navigation Key | Description |
|----------------|-------------|
| `H` | Go to the first line of current screen. A mnemonic for H is "home" position - "0,0" a.k.a. the upper left corner of the screen |
| `M` | Go to the middle line of current screen |
| `L` | Go to the last line of current screen |

## Redraw Screen with Current Line on Top, Bottom or Middle

| Navigation Key | Description |
|----------------|-------------|
| `z\<ENTER\>` | Redraw the screen with the current line under the cursor at the top of the screen. |
| `z-` | Redraw the screen with the current line under the cursor at the bottom of the screen. |
| `z.` | Redraw the screen with the current line under the cursor at the middle of the screen. |

## Navigate to Top and Bottom of the File

| Navigation Key | Description |
|----------------|-------------|
| `:0` | Go to the top of the file – method 1 |
| `gg` | Go to the top of the file – method 2 |
| `1G` | Go to the top of the file – method 3 |
| `:$` | Go to the bottom of the file – method 1 |
| `G`  | Go to the bottom of the file – method 2 |

## Navigate to Nth Character, Nth Percentage of a File

| Navigation Key | Description |
|----------------|-------------|
| `50%` | Go to the 50th percentage of file. Jump to the middle of the  file.
| `75%` | Go to 75% of the file. Jump to 3/4 th of the file. |
| `100l` | 100 followed by l. Go to the 100 th character from current position |
| `100<space>` | 100 followed by empty space. Another way to go to the 100 th character from current position |
| `:goto 25` | Go to 25 th character from the start of file |
| `25|` | 25 followed by pipe symbol Go to 25 th character in the current line |

## Line Number Navigation

| Command | Description |
|---------|-------------|
| `:set number` | Display line numbers |
| `:set nu`     | Display line numbers |
| `:set nonumber` | Do not display line numbers |
| `:set nonu` | Do not display line numbers |
| `:set numberwidth=5` | By default the line number width is set to 4 characters. You can change this to 5 character using numberwidth |

| Navigation Key | Description |
|----------------|-------------|
| `:50`  | Go to the 50 th line |
| `50gg` | Another way to jump to 50 th line |
| `50G`  | Another way to jump to 50 th line |

## Source Code Navigation

| Navigation Key | Description |
|----------------|-------------|
| `%` | Go to the matching character of the pair. Jump to the matching parenthesis (), or curly braces {} or square bracket []. |
| `[(` | Go to the previous unmatched ( |
| `[)` | Go to the previous unmatched ) |
| `[{` | Go to the previous unmatched { |
| `[}` | Go to the previous unmatched } |

## Navigate From Insert Mode

| Navigation Key | Description |
|----------------|-------------|
| `SHIFT-<Right Arrow>` | Go to right word-by-word in insert mode |
| `SHIFT-<Left Arrow>`  | Go to left word-by-word in insert mode |

## Jump Using CTRL-O and CTRL-I

| Jump Navigation | Description |
|-----------------|-------------|
| `CTRL-O`  | Jump back to previous spot |
| `CTRL-I`  | Jump forward to next spot |
| `5CTRL-O` | Jump to location#5 shown above location#0 |
| `5CTRL-I` | Jump to location#5 shown below location#0 |

## Navigate Within a Very Long Line

| Navigation Key | Description |
|----------------|-------------|
| `gj` | Scroll down a visual line |
| `gk` | Scroll up a visual line |
| `g^` | Go to the starting of current visual line |
| `g$` | Go to the end of current visual line |
| `gm` | Go to the middle of current visual line |

## Vim Command Line Navigation

| Command Line | Description |
|--------------|-------------|
| `$ vim +143 <filename>` | Go to the 143rd line of file |
| `$ vim +/search-term <filename>` | Go to the first match of the specified search term from top |
| `$ vim +?search-term <filename>` | Go to the first match of the specified search term from bottom |
| `$ vim -t TAG` | Go to the specific tag |

## Create Local Bookmarks inside file using Marks

| Bookmark Command | Description |
|------------------|-------------|
| `ma` | Bookmark the current location with name 'a' |
| `\`a (backtick a)` | Jump to the exact location of bookmark 'a' |
| `'a (single quote a)` | Jump to the beginning of the line containing the bookmark 'a' |
| `:marks` | display list of all bookmarks |

## Default Marks

| Default Marks | Description |
|----------------|-----------------
| `\`"`   | To the position where you did last edit before exit |
| `\`[`   | To the first character of previously changed or yanked text |
| `\`]`   | To the last character of previously changed or yanked text |
| `'<`    | To the first line of previously selected visual area |
| `'>`    | To the last line of previously selected visual area |
| `'.`    | To the position of where the last change was made |
| `'^`    | To the position where the cursor was the last time when insert mode was stopped |
| `ma`    | Creates a bookmark called `a` |
| `\`a`   | Jump to the exact location (line and column) of the bookmark `a` |
| `'a`    | Jump to the beginning of the line of the bookmark `a` |
| `:marks` | Display all the bookmarks |
| `:marks a` | Display the details of the bookmark with name `a` |
| `\`.` | Jump to the exact location (line and column) where the last change was performed |

## Insert or Append Text

| Key            | Description |
|----------------|-----------------
| `i`            | Insert text at current position |
| `I`            | Insert text at the beginning of the line |
| `o`            | Insert a new line after the current line and insert text |
| `O`            | Insert a new line before the current line and insert text  |
| `:r FILENAME`  | Insert another file content into current file after the current line  |
| `:r! COMMAND`  | Insert output of a command into current file after the current line  |
| `a`            | Append text after the current cursor position |
| `A`            | Append text to the end of the line |
| `r{c}`         | To replace a single character with the single character {c} |
| `R`            | To replace character until you press <ESC> |
| `s` | Substitue the current character with new character |
| `S`| Substitue the current line with new text |
| `4s` | Substitue 4 character (from current position) with new text |
| `4S` | Substitue 4 lines (from current line) with new text |
| `cc` | Change the whole current line (same as `S`) |
| `C` | Change the current line from the current cursor position |
| `J` | Join two lines |
| `:set nojoinspaces` | Always use one space when joining two lines |

## Copy (yank)
| Key            | Description |
|----------------|-----------------
| `y<char navigation keys>` | To copy a single character |
| `y<word navigation keys>` | To copy a single word |
| `y<line navigation keys>` | To copy a single line |
| `y<mark name>` | To copy up to a bookmarked line |
| `y\`<mark name>` | To copy up to a bookmarked position |
| `yM` | To copy up to the line at the middle of the screen |
| `p` | Paste immediately after the current cursor location |
| `P` | Paste immediately before the current cursor location |
| `x` | Delete the current character |
| `dw` | Delete the current word |
| `dj` | Delete the current line and next line |

## Insert Content from Clipboard Buffer

| Shift-Insert | [Insert Mode] Paste clipboard content to editor |
| `"\*p"` | [Normal mode] Paste clipboard content to editor |
| `:%y+`  | Copy the whole file to clipboard |
| `:y+` | Copy the current line from the file to clipboard |
| `:n,my+` | Copy specific range from file to clipboard |

## Editing with :g (global)

| Example | Description |
|---------|-------------|
| `:g/^$/d` | Delete all empty lines in the file |
| `:g/^\s\*$/d` | Delete all empty and blank lines in the file |
| `:g/^S/,/./-j` | Reduce multiple blank lines into a single blank line |
| `:g/pattern/d` | Delete the line which has a specific pattern |
| `:g/pattern/. w>\>filename` | Extract lines with specific pattern and write it into another file |
| `:g/^/m0` | Reverse a file |
| `g!/pattern/d` | Delete all lines except the one matching pattern |
| `v/pattern/d` | Delete all lines except the one matching pattern |


## Copy Lines to Named Buffer
| Command | Description |
|---------|-------------|
| `"ayy` | Copy current line to buffer `a` |
| `"a5yy` | Copy 5 lines to buffer `a` |
| `"ap` | Paste copied lines from buffer `a` after the cursor |
| `"aP` | Paste copied lines from buffer `a` before the cursor |
| `<Ctrl>-G` | View basic file details |
| `g<Ctrl>-G` | View advance file details |

