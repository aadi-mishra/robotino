namespace Encoder {

	const int enc_lA = 3;
	const int enc_lB = 20;
	const int enc_rA = 2;
	const int enc_rB = 21;
	const int enc_bA = 18;
	const int enc_bB = 19;

	int current_pulser;
	int current_pulsel;
	int current_pulseb;

	int prev_pulser;
	int prev_pulsel;
	int prev_pulseb;

	int motors_pulse_r;
	int motors_pulse_l;
	int motors_pulse_b;

	int encValRA;
	int encValRB;
	int encValLA;
	int encValLB;
	int encValBA;
	int encValBB;

	void readEncoders(){
		encValRA = digitalRead(enc_rA);
		encValRB = digitalRead(enc_rB);
		encValLA = digitalRead(enc_lA);
		encValLB = digitalRead(enc_lB);
		encValBA = digitalRead(enc_bA);
		encValBB = digitalRead(enc_bB);
	}

	void motors_count_pulse_rA() {
		if (encValRA != encValRB){
			current_pulser--;
		}
		else {
			current_pulser++;
		}
	}

	void motors_count_pulse_rB() {
		if (encValRA != encValRB){
			current_pulser++;
		}
		else {
			current_pulser--;
		}
	}

	void motors_count_pulse_lA() {
		if (encValLA != encValLB){
			current_pulsel--;
		}
		else {
			current_pulsel++;
		}
	}

	void motors_count_pulse_lB() {
		if (encValLA != encValLB){
			current_pulsel++;
		}
		else {
			current_pulsel--;
		}
	}

	void motors_count_pulse_bA() {
		if (encValBA != encValBB){
			current_pulseb--;
		}
		else {
			current_pulseb++;
		}

	}

	void motors_count_pulse_bB() {
		if (encValBA != encValBB){
			current_pulseb++;
		}
		else {
			current_pulseb--;
		}

	}

	int get_motors_pulse_r() {
		return motors_pulse_r;
	}
	int get_motors_pulse_l() {
		return motors_pulse_l;
	}
	int get_motors_pulse_b() {
		return motors_pulse_b;
	}
	
	void initEncoder() {


		pinMode(enc_rA, INPUT_PULLUP); //Enc R channel A
		pinMode(enc_rB, INPUT_PULLUP); //Enc R channel B
		
		pinMode(enc_lA, INPUT_PULLUP); // Enc L channel A
		pinMode(enc_lB, INPUT_PULLUP);  //Enc L channel B

		pinMode(enc_bA, INPUT_PULLUP); // Enc B channel A
		pinMode(enc_bB, INPUT_PULLUP); // Enc B channel B

		readEncoders();

		attachInterrupt(0, motors_count_pulse_rA, RISING);
		attachInterrupt(2, motors_count_pulse_rB, RISING);

		attachInterrupt(1, motors_count_pulse_lA, RISING);
		attachInterrupt(3, motors_count_pulse_lB, RISING);

		attachInterrupt(5, motors_count_pulse_bA, RISING);
		attachInterrupt(4, motors_count_pulse_bB, RISING);
		interrupts();

	}
	
	void updateState() {
		//readEncoders();
		motors_pulse_r = current_pulser;
		current_pulser = 0;

		motors_pulse_l += current_pulsel;
		current_pulsel = 0;

		motors_pulse_b += current_pulseb;
		current_pulseb = 0;
	}

}


