// O(N^4) time; O(N) memory
typedef struct {
    int number;
    char times_using_number;
} Combination;

typedef struct {
    Combination *combinations;
    char combinationsSize;
} Combinations;

typedef struct {
    int **results;
    Combinations *combinations;
    int resultSize;
} Result;

/**
 * It tells how many different numbers they are.
 * Ex: [1,2,1] will tell "there's two ones and one two". Output sorted.
 * /!\ Remember to call free(result.combinations) /!\
 * Time O(1), space O(1)
 */
Combinations calculate(int a, int b, int c) {
    Combination *retorno = (Combination*)malloc(sizeof(Combination));
    retorno[0].number = a;
    retorno[0].times_using_number = 1;
    int size = 1;
    
    if (a == b) {
        retorno[0].times_using_number++;
        
        if (b == c) retorno[0].times_using_number++;
        else {
            retorno = (Combination*)realloc(retorno, sizeof(Combination)*2);
            retorno[1].number = c;
            retorno[1].times_using_number = 1;
            size++;
            
            if (a > c) {
                // sort
                Combination tmp = retorno[1];
                retorno[1] = retorno[0];
                retorno[0] = tmp;
            }
        }
    }
    else {
        retorno = (Combination*)realloc(retorno, sizeof(Combination)*2);
        retorno[1].number = b;
        retorno[1].times_using_number = 1;
        size++;
        
        if (a > b) {
            // sort
            Combination tmp = retorno[1];
            retorno[1] = retorno[0];
            retorno[0] = tmp;
        }
        
        if (retorno[0].number == c) retorno[0].times_using_number++;
        else if (retorno[1].number == c) retorno[1].times_using_number++;
        else {
            retorno = (Combination*)realloc(retorno, sizeof(Combination)*3);
            retorno[2].number = c;
            retorno[2].times_using_number = 1;
            size++;
            
            // sort
            if (retorno[1].number > c) {
                Combination tmp = retorno[2];
                retorno[2] = retorno[1];
                retorno[1] = tmp;
            }
            if (retorno[0].number > retorno[1].number) {
                Combination tmp = retorno[1];
                retorno[1] = retorno[0];
                retorno[0] = tmp;
            }
        }
    }
    return (Combinations){retorno, size};
}

bool compare(Combinations a, Combinations b) {
    if (a.combinationsSize != b.combinationsSize) return false;
    for (int x = 0; x < a.combinationsSize; x++) {
        if (a.combinations[x].number != b.combinations[x].number
            || a.combinations[x].times_using_number != b.combinations[x].times_using_number) return false;
    }
    return true;
}

/**
 * It will check if the combination [a,b,c] it's already picked.
 * '*retorn' will contain the 'calculate(a, b, c)' if the return value is false
 * /!\ Remember to call free(retorn.combinations) if return value false /!\
 * time O(n) space O(1)
 */
bool picked(Result *result, Combinations *retorn, int a, int b, int c) {
    bool found = false;
    Combinations current = calculate(a, b, c);
    
    for (int x = 0; x < result->resultSize && !found; x++) {
        if (compare(current, result->combinations[x])) found = true;
    }
    
    if (found) free(current.combinations);
    else *retorn = current;
    
    return found;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    Result retorno = (Result){NULL,NULL,0};
    *returnColumnSizes = NULL;
    
    for (int x = 0; x < numsSize; x++) {
        for (int y = x+1; y < numsSize; y++) {
            for (int z = y+1; z < numsSize; z++) {
                if (nums[x]+nums[y] != -nums[z]) continue; // nums[x]+nums[y]+nums[z] == 0
                
                Combinations aux;
                if (picked(&retorno, &aux, nums[x], nums[y], nums[z])) continue;
                
                retorno.resultSize++;

                retorno.results = (int**)realloc(retorno.results, sizeof(int*)*retorno.resultSize);
                int *tmp = (int*)malloc(sizeof(int)*3); // always 3
                tmp[0] = nums[x];
                tmp[1] = nums[y];
                tmp[2] = nums[z];
                retorno.results[retorno.resultSize-1] = tmp;

                retorno.combinations = (Combinations*)realloc(retorno.combinations, sizeof(Combinations)*retorno.resultSize);
                retorno.combinations[retorno.resultSize-1] = aux;

                *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int)*retorno.resultSize);
                (*returnColumnSizes)[retorno.resultSize-1] = 3; // always 3
            }
        }
    }
    
    // free combinations
    for (int x = 0; x < retorno.resultSize; x++) free(retorno.combinations[x].combinations);
    free(retorno.combinations);
    
    *returnSize = retorno.resultSize;
    return retorno.results;
}