
class Monomer {
	private:
		double position, force, velocity;
	
	public:
		double Get_position();
		
		double Get_force();
		voide Reset_force();
		double Add_force(double df);
}
	
