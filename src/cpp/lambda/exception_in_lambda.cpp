using TNoexceptVoidFunc = void(*)() noexcept;
void SimpleNoexceptCall(TNoexceptVoidFunc f) { f(); }

using TVoidFunc = void(*)();
void SimpleCall(TVoidFunc f) { f(); }

void fNoexcept() noexcept {}
void fRegular() {}

int main()
{
	SimpleNoexceptCall(fNoexcept);
	SimpleNoexceptCall([]()noexcept{});

	SimpleCall(fNoexcept);
	SimpleCall(fRegular);
	SimpleCall([]()noexcept {});
	SimpleCall([](){});
}
