-- defines a factorial function
function fun (n)
	if n == 0 then
		return 1
	else
		return n * fun(n-1)
	end
end

function fact()
	print("enter a number:")
	a = io.read("*number")        -- read a number
	val = fun(a)
	print(val)
	return val
end