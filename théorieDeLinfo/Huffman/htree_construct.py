# Auxiliary functions for constructing a Huffman tree from a string


from htrees import *
#### ONLY FOR #readfile######
"""
from htree_dot_noviz import display_htree

from htree_construct import *
from bitstring import *

# Boolean constant determining whether trees are displayed with graphviz-dot
display_tree_constant = True

# name suffix for file containing coded/ decoded text
fn_cod_suffix_constant = "_coded"
fn_dec_suffix_constant = "_decoded"


def read_file_latin1 (filename):
    with open(filename + ".txt", encoding='ISO-8859-1') as fn:
        return (fn.read())
"""

#----------------------------------------------------------------------
# Compute character distibution from input string

#----------------------------------------------------------------------

# ex5 incremente valeur d'une clé spécifique d'un dictionnaire
def increment(dico, key): # if not in dico add clé/val au dico
    if key not in dico:
        dico[key] = 1  # add unexisting key/value
    else:
        dico[key] += 1 # increment value
    return dico

def ch_distrib(entryDico):    ### calculate the frequence distribution for a string
    dico_freq = {}
    lenghtFreqStr = float(len(entryDico))
    for c in entryDico:         # for each element in the string:
        if c not in dico_freq:  # if the element is not in the dictionnary add it with value 1 
            dico_freq[c] = 1
        else:                   # if the element not in the dictionnary add 1 to the value 
            dico_freq[c] += 1
    for k in dico_freq:  # divide each element with the string length
        dico_freq[k] /= lenghtFreqStr  
    return dico_freq

 #print(ch_distrib(read_file_latin1("miserables"))) ############# Uncomment paragraph under 'from htrees import *' to make the readfile fonction work
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
