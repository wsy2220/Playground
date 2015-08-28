/* merge a[na] and b[nb] into result[na+nb] */
void merge(int *result, int *a, int *b, int na, int nb)
{
	int i, n = na + nb;
	int j = 0, k = 0;
	for(i = 0; i < n; i++){
		if(j < na && (k >= nb || a[j] < b[k])){
			result[i] = a[j];
			j++;
		}
		else{
			result[i] = b[k];
			k++;
		}
	}
}

