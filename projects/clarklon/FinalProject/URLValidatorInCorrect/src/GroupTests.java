import java.io.*;
import java.util.Scanner;
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class GroupTests extends TestCase {
	
	public GroupTests(String testName) {
	      super(testName);
	   }
   
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing
	   //Variable declaration
	   int i = 1;
	   Scanner scanner = new Scanner(System.in);
	   UrlValidator myURL = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   //User prompt
	   System.out.println("-----------Manual Test Suite-----------\nEnter URL to test, type 'quit' to exit.\n");
	   
	   //Forever loop, until user quits
       while (true) {
    	   //Test case number
    	   System.out.println("Manual Test " + i);
    	   
    	   //Get input
           System.out.print("Enter a URL to test: ");
           String manualURL = scanner.nextLine();

           if ("quit".equals(manualURL)) {
        	   System.out.println("\n");
        	   break;
           }
           else {
        	   System.out.println(manualURL + " = " + myURL.isValid(manualURL) + "\n");
        	   i++;
           }
           
       }

       scanner.close();
   }
   
   public void testPortPartition()
   {
       UrlValidator urlVal = new UrlValidator(
               null,null, UrlValidator.ALLOW_ALL_SCHEMES);
       //valid case of basic setup works just fine.
       assertTrue(urlVal.isValid("http://www.google.com/"));
       //valid case, only added port on. Failed.BUG
       assertTrue(urlVal.isValid("http://www.google.com:80"));
       assertTrue(urlVal.isValid("telnet://192.9.2.16:80"));

   }

   public void testSchemePartition()
   {
       UrlValidator urlVal = new UrlValidator(
               null,null, UrlValidator.ALLOW_ALL_SCHEMES);

       //valid case BUG
       assertTrue(urlVal.isValid("file://www.google.com"));
       assertTrue(urlVal.isValid("ftp://www.google.com"));
       assertTrue(urlVal.isValid("h3t://www.google.com"));
       assertTrue(urlVal.isValid("www.google.com"));
       assertTrue(urlVal.isValid("mailto:John.Doe@example.com"));
       assertTrue(urlVal.isValid("data://www.google.com"));
       assertTrue(urlVal.isValid("telnet://192.9.2.16"));


       assertTrue(urlVal.isValid("http://www.google.com"));
       assertTrue(urlVal.isValid("https://www.google.com"));
       //valid case BUG
       assertTrue(urlVal.isValid("file://www.google.com/test"));
       //valid case BUG
       assertTrue(urlVal.isValid("file://www.google.com:80"));

       //valid case
       assertTrue(urlVal.isValid("http://www.google.com/test"));

       assertTrue(urlVal.isValid("http://www.google.com:80"));
       // /valid case BUG SEE TEST PORT PARTITION
   }
   
   public void testAuthorityPartition()
   {
      UrlValidator urlVal = new UrlValidator(null,
              null, UrlValidator.ALLOW_ALL_SCHEMES);
      //nullable authorities
       assertTrue(urlVal.isValid("file://"));//null authority w/ file **BUG
       assertFalse(urlVal.isValid("http://"));//**BUG
       assertFalse(urlVal.isValid("https://"));//**BUG
       assertTrue(urlVal.isValid("file:///test")); //**BUG
       assertFalse(urlVal.isValid("http:///test")); //**BUG
       assertFalse(urlVal.isValid("https:///test")); //**BUG


      assertTrue(urlVal.isValid(
              "file:///E:/downloads/school/cs362/FinalProject-Part-B.pdf"));
      //real URL  BUG.

       //Due to passing of http with anonymous.
       // attempted to see if it at all works.
       // truly this should be a false, not a true.
       assertTrue(urlVal.isValid(
               "http:///E:/downloads/school/cs362/FinalProject-Part-B.pdf"));
       //testing to see if goes through, really should be false.
       //FAILURE of this case. Path not being properly accepted
   } 
  
   public void testIsValid()
   {
	   //You can use this function for programming based testing   
	   //Variable declaration
	   int i, j, k, l, m;
	   int testNum = 1;
	   UrlValidator myURL = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	  
	   //Scheme array
	   String[] schemeArray = {"http://", "", "##"};
	   boolean[] schemeResults = {true, false, false};
	   
	   //Authority array
	   String[] authorityArray= {"www.google.com", "www.bing.com", "209.10.101.10", "500.50.500.50", "34f"};
	   boolean[] authorityResults = {true, true, true, false, false};
	   
	   //Port array
	   String[] portArray = {"",":0",":65535",":65536",":6a"};
	   boolean[] portResults = {true, true, true, false, false};
	   
	   //Path array
	   String[] pathArray = {"", "/34/1/4ff.aspx", "/home/nextpage.html","/?a=1",":0"};
	   boolean[] pathResults = {true, true, true, false, false};
	   
	   //Query array
	   String[] queryArray = {"", "?a=1", "?a=1&movie=thebestone&tvshow=gilmoregirls&animal=fefe&children=two&anniversary=14&homework=almostdone", "&a=1?b=2"};
	   boolean[] queryResults = {true, true, true, false};
	   
	   //Construct URL arrays and run tests
	   for(i = 0; i < schemeArray.length; i++)
	   {
		   for(j = 0; j < authorityArray.length; j++)
		   {
			   for(k = 0; k < portArray.length; k++)
			   {
				   for(l = 0; l < pathArray.length; l++)
				   {
					   for(m = 0; m < queryArray.length; m++)
					   {
						   String compositeURL = (schemeArray[i] + authorityArray[j] + portArray[k] +  pathArray[l] + queryArray[m]);
						   if((schemeResults[i] == true && authorityResults[j] == true && portResults[k] == true && pathResults[l] == true && queryResults[m] == true && myURL.isValid(compositeURL) == true) || ((schemeResults[i] == false || authorityResults[j] == false || portResults[k] == false || pathResults[l] == false || queryResults[m] == false) && myURL.isValid(compositeURL) == false))
						   {
							   System.out.println("Test " + testNum + "\n" + "Test PASSED - " + compositeURL + " = " + myURL.isValid(compositeURL) + "\n");
						   }
						   else
						   {
							   System.out.println("Test " + testNum + "\n" + "Test FAILED - " + compositeURL + " = " + myURL.isValid(compositeURL) + "\n");
						   }
						   testNum = testNum + 1;
					   }
				   }
			   }
		   }
	   }
   }
}
