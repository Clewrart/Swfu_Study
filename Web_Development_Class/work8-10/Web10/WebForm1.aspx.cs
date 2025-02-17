using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;
using MySql.Data.MySqlClient;

namespace Web10
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }


        public static string connectionString = "data source=localhost;database=studmanage;user id=root;password=805345;pooling=true;charset=utf8mb4;";

        [WebMethod]
        public static bool UserIsValid(string name, string psw)
        {
            using (MySqlConnection conn = new MySqlConnection(connectionString))
            {
                conn.Open();

                string query = "SELECT COUNT(*) FROM userinfo WHERE UserName = @username AND Password = @password";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@username", name);
                    cmd.Parameters.AddWithValue("@password", psw);
                    int count = Convert.ToInt32(cmd.ExecuteScalar());
                    return count > 0;

                }

               
            } 
        }

        [WebMethod]
        public static bool UserIsexist(string name)
        {
            using (MySqlConnection conn = new MySqlConnection(connectionString))
            {
                conn.Open();

                string query = "SELECT COUNT(*) FROM userinfo WHERE UserName = @username ";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@username", name);
                   
                    int count = Convert.ToInt32(cmd.ExecuteScalar());
                    return count > 0;

                }


            }
        }

    }
    
}