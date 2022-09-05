program P2 ;


procedure printArr(var arr : array of integer ; var n : integer ) ;
{
    Input: an array and its length

    Print out the array 
}
var 
    i : integer ;

begin
    for i := 0 to n-1 do
        begin
            {write ( arr[i] , ' ' ) ;}
        end ;
    writeln();
end;


procedure merge(var arr_A,arr_B,final_arr:array of integer; var len_A, len_B:integer);
{   
    Input: array a,b,c && size of array a: m && size of array b:n 
    Return: merged array a and b into a sorted array c
    
    This function will loop through array a and b. While looping through, it will
    compare the elements of array a and b; after that, it will place the elements into array c
    in the ascending order.
}
var 
    i,j,k:integer;  

begin
    i:=0;
    j:=0;
    k:=0;
    
    while((i < len_A)  and (j < len_B)) do
        begin
            if(arr_A[i] < arr_B[j]) then
                begin
                    final_arr[k] := arr_A[i]; 
                    i := i+1; 
                    k := k+1;
                end;
            if(arr_A[i] >= arr_B[j])then
                begin
                    final_arr[k] := arr_B[j];
                    j := j+1;
                    k := k+1;
                end;
        end;
    while(i < len_A) do
        begin
            final_arr[k] := arr_A[i];
            i := i+1;
            k := k+1;
        end;

    while(j < len_B) do
        begin
            final_arr[k] := arr_B[j];
            j:=j+1;
            k:=k+1;
        end;
end;


var 
    arr_A:array [1..20] of integer;    
    arr_B:array [1..20] of integer;         
    final_arr:array [1..40] of integer;
    len_A, len_B, i, n:integer;

begin
    {
        Input: 2 arr inputs from the keyboard
        Output: A merged array of the 2 input arrays sorted in the ascending order
    }

    i := 1;
    
    writeln('Please input the first list of integer (MAX: 20 int):');
    read(arr_A[i]);
    
    while not eoln do //Read until the end of the line
        begin
            i := i+1;
            read(arr_A[i]);
        end;

    len_A := i; //Size of array A

    i := 1;

    writeln('Please input the second list of integer (MAX: 20 int):');
    read(arr_B[i]);

    while not eoln do
        begin
            i := i+1;
            read(arr_B[i]);
        end;
    len_B := i;

    writeln('==================================');
    // print the first and second array as confirmation of correct input
    writeln('First input array: ');
    printArr(arr_A, len_A);
    writeln('Second input array: ');
    printArr(arr_B, len_B);
    n := len_A + len_B; //Size of final array
    writeln('==================================');
    
    Merge(arr_A, arr_B, final_arr, len_A, len_B);
    writeln('Final array: ');
    printArr(final_arr, n);

end.