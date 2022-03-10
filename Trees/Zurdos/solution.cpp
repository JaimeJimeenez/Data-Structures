

// Primera componente: si es zurdo o no
// Segunda componente: numero de nodos 
pair<bool, int> es_zurdo_aux(const BinTree<int>& t) {
    if (t.empty())
        return {true, 0};
    else {
        if (t.left().empty() && t.right().empty())
            return {true, 1};
        auto [es_zurdoIz, num_nodos_izq] = es_zurdo_aux(t.left());
        auto [es_zurdoDer, num_nodos_der] = es_zurdo_aux(t.right());

        return {es_zurdo_iz && es_zurdo_der && num_nodos_iz > num_nodos_der, num_nodos_iz + num_nodos_der + 1}
    }
}

bool es_zurdo(const BinTree<int> t) {
    return es_zurdo_aux(t).first;
}