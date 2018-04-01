# lama
_Lama, the application that does not mache these words._

## Description
Lama is a GNU Linux tool for mixing a word list.
The  goal is to obtain a custom password dictionary to a particular target, whether physical or moral.

It is therefore important that the words in this list correspond to the target.

Keep in mind that the Lama generates a simple password list and not complex, this goal is to be fast and targeted rather than slow and exostif.

## Compilation
### Install
Note that the make install must be run as **root**, because the binary was copy to **/bin** and configurations file into **/etc/lama**.

`make`

`make install`

or

`make all`

or

`make re`

### uninstall
Note that the make uninstall must be run as **root**, because the binary was remove from **/bin** and configurations file from **/etc/lama**.

`make uninstall`

### clean

`make clean`

or

`make fclean`


## Utilisation
First, you must create a word list with personnal infomations about the target. Then you can use **lama** to mix your given work list:

`lama 1 4 /tmp/list -ncCyh > /tmp/dico`

For more detail, see `man lama`
