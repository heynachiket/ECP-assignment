


echo -n "bhai no input me de muze check krne ki chull hai ki vo -ve hai +ve hai ya fir 0 = "
read n

if [ $n -lt 0 ]
then
	echo "bhai no to Negative hai"
elif [ $n -gt 0 ]
then
	echo "bhai no to Postive hai bilkul teri tarah"
else
	echo "chikne tune jo dala vo no 0 hai"
fi
