#include "IDisplayModule.hpp"

class Dyn : public IDisplayModule {
	public:
		Dyn();
		~Dyn();

		void init() override;
		void stop() override;
		const std::string &getName() const override;
	private:
		std::string name;
};