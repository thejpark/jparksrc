/*
String.method('deentityify', function ( ) {
            var entity = {
            quot: '"',
            lt: '<',
            gt: '>'
            };

            return function ( ) {
                return this.replace( /&([^&;]+);/g,
                                function(a, b) 
                                {
                                    var r = entity[b];
                                    return typeof r === 'string' ? r : a;

                                }
                            );
            };
        }( ));

debug('&lt;&quot;&gt;'.deentityify()); // <">
*/

/*
String.method('jung', function() 
        {
            debug(this);
            debug('jung');
        });

        
debug('test'.jung());
*/

var fibonacci = (function() 
        {

            var memo = [0, 1];
            var fib = function (n) {
                var result = memo[n];

                if (typeof result !== 'number') {
                    result = fib(n - 1) + fib(n - 2);
                    memo[n] = result;
                }

                return result;

            };
            return fib;
        }());

debug(fibonacci(4));


var fibo = function (i) 
{
    return i < 2 ? i : fibo(i - 1) + fibo(i - 2);
    
};

debug(fibo(4));


var ia = [1, 2, 'this'];

debug(ia[0]);
debug(ia[2]);


        


                
                        
                                    

            