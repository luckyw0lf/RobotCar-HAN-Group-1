//GPL-3.0-only
#ifndef TOYCAR_H_
 #define TOYCAR_H_

//uart string operations
//
//toycar_set_spd_direction will set global_spd and global_direction
//according to a passed string
//
//format: 9f\n
//format: 4l\n

void toycar_set_spd_direction(unsigned int speed, unsigned char direction);

void set_motorsA_forward();
void set_motorsA_backwards();

void set_motorsB_forward();
void set_motorsB_backwards();

#endif // TOYCAR_H_
