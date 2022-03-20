#include <iostream>

//Necesitas saber el primer  y el ultimo elemento de los arboles derechos e izquierdos respectivamente

std::tuple<bool, int, int> ascendente_denso_aux2(const BinTree<int> &arbol) {
    if (arbol.empty()) 
        return { true, -1, -1 };
    auto [densoIzq, prim_izq, ult_izq] = ascendente_denso_aux(arbol.left());
    auto [densoDer, prim_der, ult_der] = ascendente_denso_aux(arbol.right());

    int prim = prim_izq != -1 ? prim_izq : arbol.root();
    int ult = prim_der != -1 ? prim_der : arbol.root();
    bool denso = denso_izq && denso_der && (ult_izq == -1 || tree.root() == ult_izq + 1) && (tree.root + 1 == prim_der || prim_der == -1);
    return [denso, prim, ult];
}

bool ascendente_denso_aux(const BinTree<int> &arbol) {
    ascendente_denso_aux2(arbol).first;
}

bool ascendente_denso(const BinTree<int> &arbol) {
    int ant = -1;
    bool denso = true;
    arbol.inorder([&ant, &denso](int x){
        if (ant != -1 && x != ant + 1)
            denso = false;
        ant = x;
    });
    return denso;
}


int main() {

}