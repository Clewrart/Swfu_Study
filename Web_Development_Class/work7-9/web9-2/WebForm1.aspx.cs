using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace web9_2
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }


        [WebMethod]
        public static string CHusr(string userName, string password)
        {
            if ((userName == "admin" || userName == "root") && password == "000000")
            {
                return "1";
            }
            else
            {
                return "0";
            }
        }

    }
   


}