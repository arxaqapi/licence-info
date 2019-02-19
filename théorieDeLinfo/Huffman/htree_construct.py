# Auxiliary functions for constructing a Huffman tree from a string


from htrees import *

#----------------------------------------------------------------------
# Compute character distibution from input string
#----------------------------------------------------------------------


#----------------------------------------------------------------------
# Construct Huffman tree from character distribution
#----------------------------------------------------------------------



#----------------------------------------------------------------------
# Construct coding table corresponding to Huffman tree
#----------------------------------------------------------------------

def dict_merge_f (d1, d2):
    dres = d1.copy()
    dres.update(d2)
    return dres


#----------------------------------------------------------------------
# Coding of a string with a coding table, resp. decoding with a Huffman tree
#----------------------------------------------------------------------
