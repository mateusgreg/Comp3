/*
 * Vector.h
 *
 *  Created on: Sep 23, 2013
 *      Author: mateus
 */

#include &lt;stdlib.h&gt;
#include &lt;iostream&gt;

#define DEFAULT_SIZE 10

template &lt;class T&gt;
class Vector {

public:
	Vector(unsigned size) {
		this-&gt;size = (size &gt; 0) ? size : DEFAULT_SIZE;
		this-&gt;vector = new T[this-&gt;size];
		//(T *)malloc(this-&gt;size * sizeof(T));
	}

	virtual ~Vector(){
		delete [] this-&gt;vector;
		//free(this-&gt;vector);
	}


	T&amp; operator [] (unsigned index) {

		if (index &lt; size) {
			return this-&gt;vector[index];
		}
		else {
			cout &lt;&lt; &quot;Index out of Bounds!&quot; &lt;&lt; endl;
		}

		/*
		try{
			if (index &gt;= size) {
				throw new ArrayIndexOutOfBounds();
			}

			return *(this + index);
		} catch (IndexOutOfBoundsException e) {

		}
		*/
	}


	void operator = (Vector* vector) {
		this-&gt;vector( vector-&gt;size );

		cout &lt;&lt; vector-&gt;size;

		for (int i=0; i &lt; vector-&gt;size; i++){
			this-&gt;vector[i] = vector[i];
		}
	}

	// const: esse m&Atilde;&copy;todo n&Atilde;&pound;o altera o estado do objeto
	void print( std::ostream&amp; o ) const {
		for( int i=0; i &lt; this-&gt;size; i++ )
			o &lt;&lt; this-&gt;vector[i] &lt;&lt; &quot; &quot;;
	}

private:
	T *vector;
	unsigned size;
};
</p></pre>