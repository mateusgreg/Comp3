<pre><p>/*
 * lambda.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: mateus
 */

#include &lt;stdio.h&gt;
#include &lt;iostream&gt;
#include &lt;algorithm&gt;
#include &lt;vector&gt;

using namespace std;

int main( int argc, char* argv[])
{
	vector&lt;vector&lt;int&gt; &gt; m = { {1, 2, 3},
			   	   	   	   	   {5, 7, 11}
			 	 	 	 	 };


	for_each(m.begin(), m.end(),
		[](vector&lt;int&gt; v){
			for_each(v.begin(), v.end(),
				[](int x){
					printf(&quot;%d &quot;, x);
				});
			printf(&quot;\n&quot;);
		}
	);


	return 0;
}
</p></pre>