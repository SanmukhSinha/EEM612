#include <bits/stdc++.h>
using namespace std;

class Knapsack
{
    protected:
        int *weights, *profits, n_items, max_weight, *order;

};

class Population : public Knapsack
{
    private:
        const int size=200;
        int **pop, *pop_profits, *pop_weights, *parent1, *parent2, *child;

    public:

        Population(int *wt, int *prf, int n, int mxwt)
        {
            setKnapsack(wt,prf,n,mxwt);
            setOrder();
            populate(n);
        }

        void setKnapsack(int *wt, int *prf, int n, int mxwt)
        {
            //creates the knapsack wt,profits
            weights = wt;
            profits = prf;
            n_items = n;
            max_weight = mxwt;
        }

        void setOrder()
        {
            int i;
            double *prf_by_wt = new double[n_items];
            order = new int[n_items];
            
            for(i=0;i<n_items;i++)
            {
                order[i] = i;
                prf_by_wt[i] = (double)profits[i]/(double)weights[i];
            }

            arraySort(prf_by_wt,order);
        }

        void populate(int n)
        {
            //Use only after knapsack is set
            int i,j,k,sum;
            srand(time(0));

            pop = new int*[size];
            pop_weights = new int[size]();
            pop_profits = new int[size]();

            for(i=0;i<size;i++)
                pop[i] = new int[n]();

            for(i=0;i<size;i++)//creating pop table
            {
                sum = 0;
                //lj = 0;
                j = rand()%n;//random starting index for randomly populating parent
                
                for(k = 0;k < n;k ++)//runs n times
                {//acts as a circular array
                
                    if(rand()%2 == 1)
                        if(sum+weights[j] <= max_weight)
                        {
                            pop[i][j] = 1;
                            sum += weights[j];
                        }
                    j = (j+1)%n;
                }
                pop_weights[i]=sum;

                for(j=0;j<n;j++)
                    if(pop[i][j]==1)
                        pop_profits[i]+=profits[j];
            }

        }

        void selection()
        {
            int choices[6],i,max,p1,p2;
            parent1 = new int[n_items];
            parent2 = new int[n_items];

            for(i=0;i<6;i++)
                choices[i]=rand()%size;
            
            max =- 99999;
            for(i=0;i<3;i++)
                if(max<pop_profits[choices[i]])
                {
                    max = pop_profits[choices[i]];
                    p1 = choices[i];
                }
            max =- 99999;
            for(i=3;i<6;i++)
                if(max<pop_profits[choices[i]])
                {
                    max = pop_profits[choices[i]];
                    p2 = choices[i];
                }

            for(i=0;i<n_items;i++)
            {
                parent1[i] = pop[p1][i];
                parent2[i] = pop[p2][i];
            }
             
            /*for(i=0;i<n_items;i++)
                cout<<parent1[i]<<" ";
            cout<<endl;
            for(i=0;i<n_items;i++)
                cout<<parent2[i]<<" ";
            cout<<endl;*/
        }

        void crossover()
        {
            child = new int[n_items];
            if(rand()%100<60)
            {
                int i,j,k,ch_wt=0;

                for(i=0;i<n_items;i++)
                {
                    child[i] = parent1[i] & parent2[i];
                    if(child[i]==1)
                        ch_wt+=weights[i];
                }
                
                j = rand()%n_items;
                for(k=0;k<n_items;k++)
                {
                    if(child[j]==0)
                        if(rand()%2==1 && weights[j]+ch_wt<=max_weight)
                        {
                            child[j]=1;
                            ch_wt+=weights[j];
                        }
                    j=(j+1)%n_items;   
                }
            }
            else 
                child = parent1;
            
            /*for(int i=0;i<n_items;i++)
                cout<<child[i]<<" ";*/
        }

        void mutation()
        {
            int i;

            for(i=0;i<n_items;i++)
                if(rand()%n_items<1)
                    child[i] = (child[i]==1)?0:1;

            repairGreedy();

            /*int chwt=0,chprf=0;
            for(i=0;i<n_items;i++)
            {
                cout<<child[i]<<" ";
                if(child[i])
                {
                    chwt+=weights[i];
                    chprf+=profits[i];
                }
            }
            cout<<chwt<<" "<<chprf<<endl;*/
        }

        bool replace()
        {
            int i, chwt=0, chprf=0, pos;
            for(i=0;i<n_items;i++)
                if(child[i]==1)
                {
                    chwt+=weights[i];
                    chprf+=profits[i];
                }

            pos = min_element(pop_profits,pop_profits+size) - &pop_profits[0];
            if(chprf > pop_profits[pos])
            {
                //cout<<chprf<<" "<<pop_profits[pos]<<endl;
                for(i=0;i<n_items;i++)
                    pop[pos][i] = child[i];

                pop_profits[pos] = chprf;
                pop_weights[pos] = chwt;

                return true;
            }
            else 
                return false;
        }

        int* getMax()
        {
            return pop[(max_element(pop_profits,pop_profits+size)-pop_profits)];
        }

        int getMaxProfit()
        {
            return *max_element(pop_profits,pop_profits+size);
        }

        void showMax()
        {
            int i,pos;
            pos = max_element(pop_profits,pop_profits+size)-pop_profits;

            cout<<"Profits: ";
            for(i=0;i<n_items;i++)
                if(pop[pos][i]==1)
                    cout<<profits[i]<<" ";
            cout<<"\nWeights: ";
            for(i=0;i<n_items;i++)
                if(pop[pos][i]==1)
                    cout<<weights[i]<<" ";
            cout<<"\nTotal Profit = "<<pop_profits[pos];
            cout<<"\nTotal Weight = "<<pop_weights[pos];
        }

        void showPop()
        {
            int i,j;

            cout<<"Population:\n";
            for(i=0;i<size;i++){
                for(j=0;j<n_items;j++)
                    cout<<pop[i][j]<<" ";
                cout<<pop_weights[i]<<" "<<pop_profits[i];
                cout<<endl;
            }
        }

        void arraySort(double *a,int *b)
        {
            int i;
            pair<double,int> pairs[n_items];

            for(i=0;i<n_items;i++)
                pairs[i] = make_pair(a[i],b[i]);

            sort(pairs,pairs+n_items);
            
            for(i=0;i<n_items;i++)
            {
                a[i] = pairs[i].first;
                b[i] = pairs[i].second;
            }
        }

        void repairGreedy()
        {
            int i,ch_wt=0;
            
            for(i=0;i<n_items;i++)
                if(child[i]==1)
                    ch_wt+=weights[i];

            i=0;
            if(ch_wt>max_weight)
            {
                while(ch_wt>max_weight && i<n_items)
                {
                    if(child[order[i]] == 1)
                    {
                        child[order[i]]=0;
                        ch_wt-=weights[order[i]];
                    }
                    i++;
                }
            }
            else if(ch_wt<max_weight)
            {
                while(ch_wt<max_weight && i<n_items)
                {
                    if(child[order[i]] == 0)
                    {
                        child[order[i]] = 1;
                        ch_wt +=weights[order[i]];
                    }
                    i++;
                }
                repairGreedy();
            }
        }

};

int main()
{
    int weights[] = {983, 982, 981, 980, 979, 978, 488, 976, 972, 486, 486, 972, 972, 485, 485, 969, 966, 483, 964, 963, 961, 958, 959},
        profits[] = {981, 980, 979, 978, 977, 976, 487, 974, 970, 485, 485, 970, 970, 484, 484, 976, 974, 482, 962, 961, 959, 958, 857},
        maxwt = 10000,
        n = 23,
        iter = 1000,
        i = 0;
    long long t_iter = 10000;
    Population p(weights,profits,n,maxwt);

    p.showPop();

    while(i<iter && t_iter--)
    {
        //cout<<i<<endl;
        p.selection();
        p.crossover();
        p.mutation();
        if(p.replace())
            i=0;
        else 
            i++;
    }

    p.showPop();
    cout<<"\n";
    p.showMax();
    return 0;
}