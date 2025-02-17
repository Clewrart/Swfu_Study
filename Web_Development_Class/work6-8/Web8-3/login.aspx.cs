using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Web8_3
{
    public partial class login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        [WebMethod]
        public static string usrLog(string p1, string p2)
        {
            if (p1 == "siyu" || p2 == "000000")
                return "1";
            else
                return "0";
        }
    }
    
}
