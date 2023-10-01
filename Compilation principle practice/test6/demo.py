import ply.lex as lex
import ply.yacc as yacc

tokens = (
    "SYMBOL",
    "COUNT"
)

t_SYMBOL = (
    r"C[laroudsemf]?|Os?|N[eaibdpos]?|S[icernbmg]?|P[drmtboau]?|"
    r"H[eofgas]?|A[lrsgutcm]|B[eraik]?|Dy|E[urs]|F[erm]?|G[aed]|"
    r"I[nr]?|Kr?|L[iaur]|M[gnodt]|R[buhenaf]|T[icebmalh]|"
    r"U|V|W|Xe|Yb?|Z[nr]")

def t_COUNT(t):
    r"\d+"
    t.value = int(t.value)
    return t

def t_error(t):
    print("Illegal character")

lex.lex()

class Atom(object):
    def __init__(self, symbol, count):
        self.symbol = symbol
        self.count = count

    def __repr__(self):
        return "Atom(%r, %r)" % (self.symbol, self.count)

def p_chemical_equation(p):
    """
    chemical_equation :
    chemical_equation : species_list
    """
    if len(p) == 1:
        p[0] = []
    else:
        p[0] = p[1]

def p_species_list(p):
    "species_list :  species_list species"
    p[0] = p[1] + [p[2]]

def p_species(p):
    "species_list : species"
    p[0] = [p[1]]

def p_single_species(p):
    """
    species : SYMBOL
    species : SYMBOL COUNT
    """
    if len(p) == 2:
        p[0] = Atom(p[1], 1)
    elif len(p) == 3:
        p[0] = Atom(p[1], p[2])

def p_error(p):
    print("Syntax error in input!")

yacc.yacc()

def atom_count(s):
    count = 0
    for atom in yacc.parse(s):
        count += atom.count
    return count

if __name__ == "__main__":
    print(atom_count("He") == 1)
    print(atom_count("H2") == 2)
    print(atom_count("H2SO4") == 7)
    print(atom_count("CH3COOH") == 8)
    print(atom_count("NaCl") == 2)
    print(atom_count("C60H60") == 120)