#include<iostream>
using namespace std;

int main()
{        //optmized bubble sort
	int value_1(0), value_2(0);
	int *p_ptr1;
	int *p_ptr2;
	int val_array[] = { 3,13,12, 4,18,5,16,2,9,22,14 };
	int my_array_size = sizeof(val_array) / sizeof(val_array[0]);
	int element_num = my_array_size;
	int array_size = my_array_size;

	//int element_num = array_size;
	while (array_size-- >0)
	{
		for (int * pp_ptr = val_array; pp_ptr<((element_num)+(val_array)-1); ++pp_ptr) // 1-off
		{
			//cout << *val_array << "    " << *val_array;
			value_1 = *pp_ptr;//    set for possible swap
			value_2 = *(pp_ptr + 1);

			if (value_1>value_2)
			{
				*pp_ptr = value_2;            //yes, swap it
				*(pp_ptr + 1) = value_1;
			}
			else
			{
				;
			} //no swap, just continue

		}

		cout << endl;
		//use below if you want to see play by play sort
		for (int * pp_ptr = val_array; pp_ptr<(my_array_size + val_array); ++pp_ptr)
		{

			//print array
			cout << *pp_ptr <<", ";

		}
		element_num--; //prevent redundancy
	} //end outer loop
	getchar();
	return  0;
}