template<typename L1, typename L2, typename... L3>
void lock(L1 &l1, L2 &l2, L3 &...l3) {
    if constexpr (is_same_v<L1, L2> && (is_same_v<L1, L3> && ...))

}
