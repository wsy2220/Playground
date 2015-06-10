void insertion(int *pool, int n)
{
	int i, j, t;
	for(i = 1; i < n; i++){
		t = pool[i];
		for(j = i - 1; j >= 0; j--){
			if(t < pool[j]){
				pool[j+1] = pool[j];
				pool[j] = t;
			}
			else
				break;
		}
	}
}
