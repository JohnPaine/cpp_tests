#include <functional>
#include <type_traits>

template<typename L1, typename L2>
struct S : L1, L2 {
	S(L1 l1, L2 l2) : L1(std::move(l1)), L2(std::move(l2)) {}

	using L1::operator();
    using L2::operator();
};

template<typename L1, typename L2>
auto make_combined(L1 &&l1, L2 &&l2) {
	return S<std::decay_t<L1>, std::decay_t<L2>> (std::forward<L1>(l1), std::forward<L2>(l2));
}

int main() {
	auto l = []() {return 4;};
  	auto l2 = [](int i) {return i * 10;};

	//auto combined = make_combined(l, l2);		// needed with -std=c++14 (c++11 doesn't know std::decay_t and can't return auto type)
    auto combined = S(l, l2);			// with -std=c++1z make_combined ain't needed anymore!
    return combined(10);
}