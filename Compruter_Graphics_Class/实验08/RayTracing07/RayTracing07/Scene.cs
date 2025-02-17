using System.Numerics;

namespace RayTracing07
{
    /**
     * 虚拟三维场景类
     */
    public class Scene
    {
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

            // 对场景中的每一个物体进行遍历
            foreach (IHitable elem in elements)
            {
                if (elem.Hit(ray, tMin, closestSoFar, tempRec))
                {
                    hitAnything = true;
                    closestSoFar = tempRec.T;

                    rec.T = tempRec.T;
                    rec.P = tempRec.P;
                    rec.N = tempRec.N;
                    rec.M = tempRec.M;
                }
            }

            return hitAnything;
        }

        public static Scene CreateScene()
        {
            Sphere sphere1 = new Sphere(
                new Vector3(0.0f, 0.0f, -2.0f),
                1.0f,
                new Lambertian(new Vector3(0.8f, 0.3f, 0.3f)));

            Sphere sphere2 = new Sphere(
                new Vector3(0.0f, -101.0f, -2.0f),
                100.0f,
                new Lambertian(new Vector3(0.8f, 0.8f, 0.0f)));

            Scene world = new Scene();

            // 将两个球体添加到虚拟场景中
            world.AddElem(sphere1);
            world.AddElem(sphere2);

            return world;
        }
    }
}
