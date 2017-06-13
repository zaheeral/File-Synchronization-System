Hardlinks cannot be perserved using the child processess as a certain meta data needs to be retained
from the parent file, this meta data needs to be changed to reflect that the node  in
the destination directory has become the parent and not in the source. Once we enter the child process
to copy the file into child node, the meta information is lost. Instead if we kept in the original
process, then it could be done.
