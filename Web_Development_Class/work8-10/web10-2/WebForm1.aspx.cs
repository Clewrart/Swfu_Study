using System;
using System.Collections.Generic;
using System.Web.Services;
using MySql.Data.MySqlClient;

namespace web10_2
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e) { }

        private static string GetConnectionString()
        {
            return "data source=localhost;database=studm;user id=root;password=805345;pooling=true;charset=utf8mb4;";
        }

        [WebMethod]//查询模块
        public static string que(string no)
        {
            if (string.IsNullOrWhiteSpace(no))
            {
                return System.Text.Json.JsonSerializer.Serialize(new List<dynamic>());
            }

            List<dynamic> students = new List<dynamic>();
            using (MySqlConnection conn = new MySqlConnection(GetConnectionString()))
            {
                try
                {
                    conn.Open();
                    string query = "SELECT * FROM studinfo WHERE studname LIKE CONCAT('%', @no, '%')";
                    using (MySqlCommand cmd = new MySqlCommand(query, conn))
                    {
                        cmd.Parameters.AddWithValue("@no", no);
                        using (MySqlDataReader reader = cmd.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                var student = new
                                {
                                    Studno = reader["studno"].ToString(),
                                    Studname = reader["studname"].ToString(),
                                    Studsex = reader["studsex"].ToString(),
                                    Email = reader["email"].ToString()
                                };
                                students.Add(student);
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    return System.Text.Json.JsonSerializer.Serialize(new { error = ex.Message });
                }
            }
            return System.Text.Json.JsonSerializer.Serialize(students);
        }

        [WebMethod]//删除模块
        public static string deleteStudent(string no)
        {
            if (string.IsNullOrWhiteSpace(no))
            {
                return "学号不能为空";
            }

            using (MySqlConnection conn = new MySqlConnection(GetConnectionString()))
            {
                try
                {
                    conn.Open();
                    string query = "DELETE FROM studinfo WHERE studno = @no";
                    using (MySqlCommand cmd = new MySqlCommand(query, conn))
                    {
                        cmd.Parameters.AddWithValue("@no", no);
                        cmd.ExecuteNonQuery();
                    }
                }
                catch (Exception ex)
                {
                    return "删除失败: " + ex.Message;
                }
            }

            return "删除成功";

        }


        [WebMethod]//编辑模块，传去增加那
        public static string editStudent(string no, string name, string sex, string email)
        {
            if (string.IsNullOrWhiteSpace(no) || string.IsNullOrWhiteSpace(name) ||
                string.IsNullOrWhiteSpace(sex) || string.IsNullOrWhiteSpace(email))
            {
                return "所有字段都必须填写";
            }

            using (MySqlConnection conn = new MySqlConnection(GetConnectionString()))
            {
                try
                {
                    conn.Open();
                    string query = "UPDATE studinfo SET studname = @name, studsex = @sex, email = @email WHERE studno = @no";
                    using (MySqlCommand cmd = new MySqlCommand(query, conn))
                    {
                        cmd.Parameters.AddWithValue("@no", no);
                        cmd.Parameters.AddWithValue("@name", name);
                        cmd.Parameters.AddWithValue("@sex", sex);
                        cmd.Parameters.AddWithValue("@email", email);
                        cmd.ExecuteNonQuery();
                    }
                }
                catch (Exception ex)
                {
                    return "更新失败: " + ex.Message;
                }
            }
            return "更新成功";
        }



        [WebMethod]//增加模块，但编辑时传过来
        public static string addStudent(string no, string name, string sex, string email)
        {
            if (string.IsNullOrWhiteSpace(no) || string.IsNullOrWhiteSpace(name) ||
                string.IsNullOrWhiteSpace(sex) || string.IsNullOrWhiteSpace(email))
            {
                return "所有字段都必须填写";
            }

            using (MySqlConnection conn = new MySqlConnection(GetConnectionString()))
            {
                try
                {
                    conn.Open();
                    string query = "INSERT INTO studinfo (studno, studname, studsex, email) VALUES (@no, @name, @sex, @email)";
                    using (MySqlCommand cmd = new MySqlCommand(query, conn))
                    {
                        cmd.Parameters.AddWithValue("@no", no);
                        cmd.Parameters.AddWithValue("@name", name);
                        cmd.Parameters.AddWithValue("@sex", sex);
                        cmd.Parameters.AddWithValue("@email", email);
                        cmd.ExecuteNonQuery();
                        
                    }
                }
                catch (Exception ex)
                {
                    return "添加失败 ";
                }
            }
            return "添加成功";
        }
    }
}
