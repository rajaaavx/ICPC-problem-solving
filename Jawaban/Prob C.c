#include <stdio.h>

int main(){
	int cases;
	scanf("%d\n", &cases);
	int nums[cases];
	for(int i=0; i<cases; i++){
		scanf("%d", &nums[i]);
	}
	int number = nums[0];
	int count=0; int direction = 0; //1 for increasing, -1 for decreasing
	for(int i=1; i<cases; i++){
		if(direction == 0){
			if(number > nums[i]) {
				count = i;
				direction = -1; //Decreasing
			}
			else if(number < nums[i]){
				count = i;
				direction = 1; //Increasing
			}
		}
		else if(direction == 1 && number >= nums[i]){
			count++; direction = -1;
		}
		else if(direction == -1 && number <= nums[i]){
			count++; direction = 1;
		}
		number = nums[i];
	}
	if(direction == 0) printf("0\n");
	else printf("%d\n", count);
	return 0;
}
