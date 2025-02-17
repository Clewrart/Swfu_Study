using System.Numerics;

namespace RayTracing05
{
    /**
     * 虚拟三维场景类
     */
    public class Scene
    {
        // 保存场景中物体的泛型列表
        public List<IHitable> elements = new List<IHitable>();

        /**
         * 添加一个物体到场景中
         */
        public void AddElem(IHitable elem)
        {
            elements.Add(elem);
        }

        /**
         * 计算光线和场景里面最近物体的交点
         */
        public bool Hit(Ray ray, float tMin, float tMax, HitRecord rec)
        {
            HitRecord tempRec = HitRecord.Empty;
            bool hitAnything = false;
            float closestSoFar = tMax;

            //对场景中每个物体进行遍历
            foreach (IHitable elem in elements)
            {
                if (elem.Hit(ray, tMin, closestSoFar, tempRec))
                {
                    hitAnything = true;
                    closestSoFar = tempRec.T;

                    rec.T = tempRec.T;
                    rec.P = tempRec.P;
                    rec.N = tempRec.N;
                }
            }
            return hitAnything;
        }

        public static Scene Build()
        {
            Scene world = new();

            // 创建2个新的球体
            Sphere sphere1 = new(
                new Vector3(0.0f, 0.0f, -2.0f),
                1.0f);
            Sphere sphere2 = new(
                new Vector3(0.0f, -101.0f, -2.0f),
                100.0f);

            world.AddElem(sphere1);
            world.AddElem(sphere2);

            return world;
        }
    }
}
