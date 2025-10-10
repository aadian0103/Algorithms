#include <ext/pb_ds/assoc_container.hpp>

template <typename T, typename U, typename Comp = std::less<T>>
using ordered_map = __gnu_pbds::tree<
    T, U, Comp,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;

template <typename T, typename Comp = std::less<T>>
using ordered_set = ordered_map<T, __gnu_pbds::null_type, Comp>;

//  auto iterator = ordered_set().find_by_order(idx); (0-indexed)
//  int num_strictly_smaller = ordered_set().order_of_key(key);