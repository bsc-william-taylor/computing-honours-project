

void kernel simple_add(global const int * A, global const int * B, global int * C) {
	int workID = get_global_id(0);
	C[workID] = A[workID] + B[workID];
}

void kernel simple_sub(global const int * A, global const int * B, global int * C) {
	int workID = get_global_id(0);
	C[workID] = A[workID] - B[workID];
}
