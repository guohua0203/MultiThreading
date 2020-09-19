#include "headers.h"
using namespace std;


vector<string> f( string s ){
    int n = s.size();  
    s = "@" + s + "#";
    vector< vector<int> > dp(2, vector<int>( n+1, 0 ) );
    for( int j = 0; j < 2; j++ ){
        dp[ j ][ 0 ] = 0;
        int rp = 0;
        int i = 1;
        while( i <= n ){
            while( s[ i - rp - 1 ] == s[ i + j + rp ] ){
                rp++;
            } 
            dp[ j ][ i ] = rp;
            int k = 1;
            while( ( dp[ j ][ i - k ] != rp - k ) && k < rp ){
                dp[ j ][ i+k ] = min( dp[j][ i - k ], rp - k );
                k++; 
            }
            rp = max( rp - k, 0 );
            i = i+k;
        }
    }
    s = s.substr( 1, n );

    vector<string> res(0);

    for( int i=1; i<=n; i++ ){
        for( int j=0; j<2; j++ ){
            for( int rp = dp[j][i]; rp > 0; rp-- ){
                res.push_back( s.substr( i - rp -1, 2 * rp + j ) ) ;
            }
        }
    }
   print_v( res ); 
    return res;
}


int main(){
    string s = "abcacbbbca";
    f(s);   
}
