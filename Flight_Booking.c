Flight_Booking()
{
	
/*
	***Departure City***
	<option selected="selected" value="Denver">Denver</option>
	<option value="Frankfurt">Frankfurt</option>
	<option value="London">London</option>
	<option value="Los Angeles">Los Angeles</option>
	<option value="Paris">Paris</option>
	<option value="Portland">Portland</option>
	<option value="San Francisco">San Francisco</option>
	<option value="Seattle">Seattle</option>
	<option value="Sydney">Sydney</option>
	<option value="Zurich">Zurich</option>
*/	

	web_reg_save_param_regexp(
		"ParamName=cDepartureCity",
		"RegExp=<option([a-z|=|\"| ]*) value=\"([A-Z|a-z| ]+)\"",
		"Group=2",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);

/*
	***Arrival City***
	<option selected="selected" value="Denver">Denver</option>
	<option value="Frankfurt">Frankfurt</option>
	<option value="London">London</option>
	<option value="Los Angeles">Los Angeles</option>
	<option value="Paris">Paris</option>
	<option value="Portland">Portland</option>
	<option value="San Francisco">San Francisco</option>
	<option value="Seattle">Seattle</option>
	<option value="Sydney">Sydney</option>
	<option value="Zurich">Zurich</option>
*/	

	web_reg_save_param_regexp(
		"ParamName=cArrivalCity",
		"RegExp=<option([a-z|=|\"| ]*) value=\"([A-Z|a-z| ]+)\"",
		"Group=2",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);
	
//	<input type="radio" name="seatPref" value="Window" />

	web_reg_save_param_ex(
		"ParamName=cSeatPreference",
		"LB=<input type=\"radio\" name=\"seatPref\" value=\"",
		"RB=\"",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);
	
//	<input type="radio" name="seatType" value="First" />	

	web_reg_save_param_ex(
		"ParamName=cSeatType",
		"LB=<input type=\"radio\" name=\"seatType\" value=\"",
		"RB=\"",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);
	
//	<input type="hidden" name=".cgifields" value="roundtrip"  />

	web_reg_save_param_ex(
		"ParamName=cCGIField1",
		"LB=<input type=\"hidden\" name=\".cgifields\" value=\"",
		"RB=\"",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);

//	<input type="hidden" name=".cgifields" value="seatType"  />

	web_reg_save_param_ex(
		"ParamName=cCGIField2",
		"LB=<input type=\"hidden\" name=\".cgifields\" value=\"",
		"RB=\"",
		"Ordinal=2",
		SEARCH_FILTERS,
		LAST);
		
//	<input type="hidden" name=".cgifields" value="seatPref"  />
	
	web_reg_save_param_ex(
		"ParamName=cCGIField3",
		"LB=<input type=\"hidden\" name=\".cgifields\" value=\"",
		"RB=\"",
		"Ordinal=3",
		SEARCH_FILTERS,
		LAST);

//	<input type="hidden" name="advanceDiscount" value="0"  />

	web_reg_save_param_ex(
		"ParamName=cAdvDiscount",
		"LB=<input type=\"hidden\" name=\"advanceDiscount\" value=\"",
		"RB=\"",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
		
	web_reg_find("Text=Find Flight",
	             "SaveCount=FindFlight_Count",
				 LAST);
				 
	lr_start_transaction("SC02_BookingFlight_T03_ClickFlights");

	web_url("Search Flights Button", 
		"URL=http://{pServerName}:{pPortNo}/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	if(atoi(lr_eval_string("{FindFlight_Count}")) > 0)
	{
		lr_end_transaction("SC02_BookingFlight_T03_ClickFlights", LR_PASS);
	}
	else
	{
		lr_end_transaction("SC02_BookingFlight_T03_ClickFlights", LR_FAIL);	
		lr_output_message("VUser ID %d encountered an error in Iteration No. %d.", atoi(lr_eval_string("{pVUserID}")), atoi(lr_eval_string("{pIterationNumber}")));
	}
	
	lr_output_message("The Departure Cities are:");
	
	while(i<=atoi(lr_eval_string("{cDepartureCity_count}")))
	{
		sprintf(deptCityVal, "{cDepartureCity_%d}", i);
		lr_output_message("%s", lr_eval_string(deptCityVal));
		i++;
	}
		
	do
	{
		deptCity = lr_paramarr_random("cDepartureCity");		
		arvlCity = lr_paramarr_random("cArrivalCity");
	}
	while(strcmp(arvlCity,deptCity) == 0);
	
	lr_save_string(deptCity, "pDepartureCity");
		
	lr_save_string(arvlCity, "pArrivalCity");
	
	seatPref = lr_paramarr_random("cSeatPreference");
	
	lr_save_string(seatPref, "pSeatPreference");
	
	seatType = lr_paramarr_random("cSeatType");
	
	lr_save_string(seatType, "pSeatType");
	
	lr_think_time(10);
	
	lr_output_message("Departure Date: %s", lr_eval_string("{pDeptDate}"));
	
	lr_output_message("Arrival Date: %s", lr_eval_string("{pReturnDate}"));
	
//	<input type="radio" name="outboundFlight" value="362;107;05/27/2020">

	web_reg_save_param_ex(
		"ParamName=cOutboundFlight",
		"LB=<input type=\"radio\" name=\"outboundFlight\" value=\"",
		"RB=\"",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);
	
//	<input type="radio" name="returnFlight" value="633;92;05/28/2020">

	web_reg_save_param_ex(
		"ParamName=cReturnFlight",
		"LB=<input type=\"radio\" name=\"returnFlight\" value=\"",
		"RB=\"",
		"Ordinal=ALL",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_find("Text=Flight departing from <B>{pDepartureCity}</B> to <B>{pArrivalCity}</B> on <B>{pDeptDate}</B>",
				 "SaveCount=FlightMessage_Count",	             
				 LAST);
	
	lr_start_transaction("SC02_BookingFlight_T04_FindFlights");
	
	web_submit_data("reservations.pl", 
		"Action=http://{pServerName}:{pPortNo}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value={cAdvDiscount}", ENDITEM, 
		"Name=depart", "Value={pDepartureCity}", ENDITEM, 
		"Name=departDate", "Value={pDeptDate}", ENDITEM, 
		"Name=arrive", "Value={pArrivalCity}", ENDITEM, 
		"Name=returnDate", "Value={pReturnDate}", ENDITEM, 
		"Name=numPassengers", "Value=2", ENDITEM, 
		"Name=roundtrip", "Value=on", ENDITEM, 
		"Name=seatPref", "Value={pSeatPreference}", ENDITEM, 
		"Name=seatType", "Value={pSeatType}", ENDITEM, 
		"Name=findFlights.x", "Value=38", ENDITEM, 
		"Name=findFlights.y", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value={cCGIField1}", ENDITEM, 
		"Name=.cgifields", "Value={cCGIField2}", ENDITEM, 
		"Name=.cgifields", "Value={cCGIField3}", ENDITEM, 
		LAST);

	if(atoi(lr_eval_string("{FlightMessage_Count}")) > 0)
	{
		lr_end_transaction("SC02_BookingFlight_T04_FindFlights", LR_PASS);
	}
	else
	{
		lr_end_transaction("SC02_BookingFlight_T04_FindFlights", LR_FAIL);	
		lr_output_message("VUser ID %d encountered an error in Iteration No. %d.", atoi(lr_eval_string("{pVUserID}")), atoi(lr_eval_string("{pIterationNumber}")));
	}

	outboundFlight = lr_paramarr_random("cOutboundFlight");
	
	lr_save_string(outboundFlight, "pOutboundFlight");
	
	returnFlight = lr_paramarr_random("cReturnFlight");
	
	lr_save_string(returnFlight, "pReturnFlight");
	
	lr_think_time(10);

//	<input type="checkbox" name="saveCC" value="on" checked="checked" />
	
	web_reg_save_param_ex(
		"ParamName=cSaveCC",
		"LB=<input type=\"checkbox\" name=\"saveCC\" value=\"",
		"RB=\"",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
	
//	<input type="hidden" name="oldCCOption" value="on"  />

	web_reg_save_param_ex(
		"ParamName=cOldCCOption",
		"LB=<input type=\"hidden\" name=\"oldCCOption\" value=\"",
		"RB=\"",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
	
//	<input type="hidden" name="JSFormSubmit" value="off"  />

	web_reg_save_param_ex(
		"ParamName=cJSFormSubmit",
		"LB=<input type=\"hidden\" name=\"JSFormSubmit\" value=\"",
		"RB=\"",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
	
//	<input type="hidden" name=".cgifields" value="saveCC"  />
	
	web_reg_save_param_ex(
		"ParamName=cCGIFields4",
		"LB=<input type=\"hidden\" name=\".cgifields\" value=\"",
		"RB=\"",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_find("Text=Save this Credit Card Information", 
				 "SaveCount=SaveCCardInfo_Count",
	             LAST);
	
	lr_start_transaction("SC02_BookingFlight_T05_SelectFlight");

	web_submit_data("reservations.pl_2", 
		"Action=http://{pServerName}:{pPortNo}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={pOutboundFlight}", ENDITEM, 
		"Name=returnFlight", "Value={pReturnFlight}", ENDITEM, 
		"Name=numPassengers", "Value=2", ENDITEM, 
		"Name=advanceDiscount", "Value={cAdvDiscount}", ENDITEM, 
		"Name=seatType", "Value={pSeatType}", ENDITEM, 
		"Name=seatPref", "Value={pSeatPreference}", ENDITEM, 
		"Name=reserveFlights.x", "Value=35", ENDITEM, 
		"Name=reserveFlights.y", "Value=8", ENDITEM, 
		LAST);

	if(atoi(lr_eval_string("{SaveCCardInfo_Count}")) > 0)
	{
		lr_end_transaction("SC02_BookingFlight_T05_SelectFlight", LR_PASS);
	}
	else
	{
		lr_end_transaction("SC02_BookingFlight_T05_SelectFlight", LR_FAIL);	
		lr_output_message("VUser ID %d encountered an error in Iteration No. %d.", atoi(lr_eval_string("{pVUserID}")), atoi(lr_eval_string("{pIterationNumber}")));
	}

	lr_think_time(10);

	web_reg_find("Text=Flight reserved",
				 "SaveCount=FlightReserved_Count",
	             LAST);
	
	lr_start_transaction("SC02_BookingFlight_T06_SetPaymentDetails");

	web_submit_data("reservations.pl_3", 
		"Action=http://{pServerName}:{pPortNo}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/reservations.pl", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={pFirstName}", ENDITEM, 
		"Name=lastName", "Value={pLastName}", ENDITEM, 
		"Name=address1", "Value={pAddress1}", ENDITEM, 
		"Name=address2", "Value={pAddress2}", ENDITEM, 
		"Name=pass1", "Value={pFirstName} {pLastName}", ENDITEM, 
		"Name=pass2", "Value={pFirstName} {pLastName}", ENDITEM, 
		"Name=creditCard", "Value={pRandNum} {pRandNum} {pRandNum} {pRandNum}", ENDITEM, 
		"Name=expDate", "Value={pExpiryDate}", ENDITEM, 
		"Name=saveCC", "Value={cSaveCC}", ENDITEM, 
		"Name=oldCCOption", "Value={cOldCCOption}", ENDITEM, 
		"Name=numPassengers", "Value=2", ENDITEM, 
		"Name=seatType", "Value={pSeatType}", ENDITEM, 
		"Name=seatPref", "Value={pSeatPreference}", ENDITEM, 
		"Name=outboundFlight", "Value={pOutboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value={cAdvDiscount}", ENDITEM, 
		"Name=returnFlight", "Value={pReturnFlight}", ENDITEM, 
		"Name=JSFormSubmit", "Value={cJSFormSubmit}", ENDITEM, 
		"Name=buyFlights.x", "Value=40", ENDITEM, 
		"Name=buyFlights.y", "Value=5", ENDITEM, 
		"Name=.cgifields", "Value={cCGIFields4}", ENDITEM, 
		LAST);

	if(atoi(lr_eval_string("{FlightReserved_Count}")) > 0)
	{
		lr_end_transaction("SC02_BookingFlight_T06_SetPaymentDetails", LR_PASS);
	}
	else
	{
		lr_end_transaction("SC02_BookingFlight_T06_SetPaymentDetails", LR_FAIL);	
		lr_output_message("VUser ID %d encountered an error in Iteration No. %d.", atoi(lr_eval_string("{pVUserID}")), atoi(lr_eval_string("{pIterationNumber}")));
	}

	lr_think_time(10);

	i = 1;

	return 0;
}