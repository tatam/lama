# lama
_Lama, the application that does not mince words._

## Description
Lama is a GNU Linux tool to generate a word list.
The  goal is to obtain a custom password dictionary to a particular target, whether physical or moral.

It is therefore important that words in this list correspond to the target.

Keep in mind that Lama generates a simple password list and not complex, the goal is to be fast and targeted rather than slow and exhaustive.

## Compilation
### Install
Note that the make install must be run as **root**, because the binary was copyed to **/bin** and configurations files to **/etc/lama**.

`make`

`make install`

or

`make all`

or

`make re`

### uninstall
Note that the make uninstall must be run as **root**, because the binary was removed from **/bin** and configurations files from **/etc/lama**.

`make uninstall`

### clean

`make clean`

or

`make fclean`


## Utilisation
![gif](https://i.imgur.com/VpunrAc.gif)
First, you must create a words list with personnal infomations about the target. Then, you can use **lama** to mix your given words list:

`lama 1 4 /tmp/list -ncCyh > /tmp/dico`

For more details, see `man lama`
