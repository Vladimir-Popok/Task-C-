/*#include "BHours.h"
#include <iostream>

int main() {
	Time t1 = Time(11, 11);
	Time t2 = Time(11, 9);
	Time t3 = Time(2, 10);
	Time t4 = Time(14, 15);
	BHours bh1 = BHours(t1, t4);
	BHours bh2 = BHours(t1, t3);

	std::cout << t1 << '\n' << t2 << '\n' << t3 << '\n' << t4 << '\n';
	if (t1 > t3) 
		std::cout << "true" << '\n';
	if (t3 < t4)
		std::cout << "false" << '\n';
	if (t1 == t1)
		std::cout << "true" << '\n';

	std::cout << t1 - t2 << '\n';
	std::cout << t2 - t1 << '\n';

	std::cout << "----------------------------------\n";
	std::cout << bh1.valid_time(Time(0, 12)) << '\n';
	std::cout << bh1.valid_time(Time(2, 12)) << '\n';
	std::cout << bh1.valid_time(Time(13, 45)) << '\n';
	std::cout << bh1.valid_time(Time(11, 11)) << '\n';
	std::cout << bh1.valid_time(Time(14, 11)) << '\n';
	std::cout << bh1.valid_time(Time(14, 16)) << '\n';
	std::cout << bh1.valid_time(Time(15, 16)) << '\n';
	std::cout << bh1.valid_time(Time(14, 15)) << '\n';
	std::cout << "----------------------------------\n";


	std::cout << "----------------------------------\n";
	std::cout << bh2.valid_time(Time(0, 12)) << '\n';
	std::cout << bh2.valid_time(Time(2, 12)) << '\n';
	std::cout << bh2.valid_time(Time(2, 10)) << '\n';
	std::cout << bh2.valid_time(Time(11, 11)) << '\n';
	std::cout << bh2.valid_time(Time(14, 11)) << '\n';
	std::cout << bh2.valid_time(Time(8, 11)) << '\n';
	std::cout << "----------------------------------\n";

	std::cout << Time::round_up(t1) << '\n';
}*/