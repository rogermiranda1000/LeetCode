/**
 * Given an end downhill it gets removed
 */
void removeBorders(int **prices, int *pricesSize) {
    /*while (*pricesSize >= 2 && (*prices)[0]>(*prices)[1]) {
        *prices++;
        (*pricesSize)--;
    }*/
    
    while (*pricesSize >= 2 && (*prices)[*pricesSize-2]>=(*prices)[*pricesSize-1]) (*pricesSize)--;
}

int maxProfit(int* prices, int pricesSize) {
    int r = 0;
    bool buying = true;
    
    removeBorders(&prices, &pricesSize);
    
    for (int x = 0; x < pricesSize; x++) {
        if (buying) {
            while (x+1 < pricesSize && prices[x]>=prices[x+1]) x++;
            buying = false;
            r -= prices[x];
        }
        else {
            while (x+1 < pricesSize && prices[x]<=prices[x+1]) x++;
            buying = true;
            r += prices[x];
        }
    }
    
    return r>0 ? r : 0;
}
