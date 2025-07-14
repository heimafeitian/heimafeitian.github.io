minikube+tomcat setup
============================================================================================================================================
https://www.cnblogs.com/builderman/p/13670012.html
	
minikube start --driver='none' --image-mirror-country='cn' --image-repository='registry.cn-hangzhou.aliyuncs.com/google_containers'  --alsologtostderr
	
#minikube start --image-mirror-country=‘cn’ --image-repository=‘registry.cn-hangzhou.aliyuncs.com/google_containers’ --base-image=‘registry.cn-hangzhou.aliyuncs.com/google_containers/kicbase:v0.0.28’

	
https://wiki.ith.intel.com/display/ValArchTeam/Install+Docker+on+Ubuntu



kubectl run hello-minikube --image=tomcat:8.0 --port=8080

kubectl expose deployment hello-minikube --type=NodePort

kubectl port-forward service/hello-minikube 7080:8080

kubectl cluster-info
	
kubectl config view

kubectl version -o json

minikube addons list

docker imgages 

kubectl describe svc hello-minikube

kubectl get pods
kubectl port-forward service/hello-minikube 7080:8080
minikube service hello-minikube


http://10.239.173.10:30347/

kubectl port-forward $(kubectl get pods --namespace=kubernetes-dashboard | grep Running | grep kubernetes-dashboard | awk '{print $1}') 9090:9090 --namespace=kubernetes-dashboard
	
	





	
