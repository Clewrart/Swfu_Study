using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace web8_2
{
    public partial class plus : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }


        [WebMethod]
        public static string Plus(string p1, string p2)
        {
            int sum = int.Parse(p1)+int.Parse(p2);
            return sum.ToString();
        }

        
    }
}