# <>
def add_mod2(nb_1, nb_2):
    return (nb_1 + nb_2) % 2


def deg(poly):
    deg_count = 0
    taille = len(poly)
    i = taille - 1

    while poly[i] == 0 and i > 0:
        deg_count -= 1
        i -= 1

    if (i == 0) or (poly == []):
        return 0
    return deg_count + taille - 1
"""
a = [0,0,1,0,0,0,0]
print(deg(a))
"""


def coeff(poly):
    taille = len(poly)
    if taille == 0:
        return 0
    return 1  # pour Z / 2Z


def is_null_poly(poly):  # ex 4
    if coeff(poly) == 1:
        return False
    return True


def add_poly(poly1, poly2):  # ok ex 5
    taille_poly_1 = len(poly1)
    taille_poly_2 = len(poly2)
    poly3 = []
    if taille_poly_1 > taille_poly_2:
        taille_poly_1, taille_poly_2 = taille_poly_2, taille_poly_1

    for i in range(taille_poly_1):
        poly3.append(add_mod2(poly1[i], poly2[i]))

    poly3.extend(poly2[taille_poly_1:])
    return poly3
# print(add_poly([0,1,1,0], [1,0,1,1,0]))


def diff_poly(poly1, poly2):
    return add_poly(poly1, poly2)


# on fait la funcion qui calcule pour un monome puis on le distribue


def mult_monome_poly(mono, poly):
    poly_fin = []
    for i in range(mono):
        poly_fin.insert(0, 0)
    return poly_fin + poly


def mult_poly(poly1, poly2):
    poly_fin = []
    taille_poly1 = len(poly1)
    for i in range(taille_poly1):
        if poly1[i] == 1:
            poly_fin = add_poly(poly_fin, mult_monome_poly(i, poly2))
    return poly_fin

# print(mult_poly([0, 1, 1], [1, 0, 1, 1]))


def eucl_poly(poly1, poly2):
    poly_quotient = []
    poly_reste = poly1[:]

    degree_poly_2 = deg(poly2)
    coeff_dominant_poly2 = coeff(poly2)

    while poly_reste != [] and deg(poly_reste) >= degree_poly_2:
        s = (coeff(poly_reste)/coeff_dominant_poly2) * \
            mult_monome_poly(deg(poly_reste) - degree_poly_2, [])# attention condition
            ## pas de * mais un if, pas de *[]
        poly_quotient = add_poly(poly_quotient, s)
        poly_reste = mult_poly(diff_poly(poly_quotient, s), poly2)
    return (poly_quotient, poly_reste)

print(eucl_poly([0, 1, 1, 0, 1], [1, 1]))


    #################
    #      2        #
    #################
# ex 10

def pad(poly, number):
    return poly + [0]*number