#include "IDisplayModule.hpp"

class Dyn2 : public IDisplayModule {
	public:
		Dyn2();
		~Dyn2();

		void init() override;
		void stop() override;
		const std::string &getName() const override;
	private:
		std::string name;
};